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

import {  AttributeModifier } from 'arkui/component/common'

import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Font, Length } from './component/units';
import { Resource } from "global.resource";
import { LengthMetrics } from "./Graphics";
import { ShadowOptions, CustomBuilder } from './component/common';
import { TextAttribute, TextOverflowOptions, TextMarqueeOptions, MarqueeState, TextSpanType, TextResponseType,
    ArkTextPeer } from './component/text';
import { ResourceColor } from './component/units';
import { FontStyle, FontWeight, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak,
    LineBreakStrategy, EllipsisMode, TextSelectableMode } from "./component/enums";
import { DecorationStyleInterface } from "./component/styledString";
import { TextDataDetectorConfig, EditMenuOptions, FontSettingOptions } from "./component/textCommon";
import { SelectionMenuOptions } from "./component/richEditor";
import { PeerNode } from "./PeerNode";

export class TextModifier extends CommonMethodModifier implements TextAttribute, AttributeModifier<TextAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize0_value?: number | string | Resource | undefined
    _minFontSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize0_value?: number | string | Resource | undefined
    _maxFontSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize0_value?: number | string | Resource | undefined
    _minFontScale_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale0_value?: number | Resource | undefined
    _fontStyle_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle0_value?: FontStyle | undefined
    _lineSpacing_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineSpacing0_value?: LengthMetrics | undefined
    _textAlign_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAlign0_value?: TextAlign | undefined
    _lineHeight_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight0_value?: number | string | Resource | undefined
    _textOverflow_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textOverflow0_value?: TextOverflowOptions | undefined
    _fontFamily_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily0_value?: string | Resource | undefined
    _maxLines_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLines0_value?: number | undefined
    _decoration_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration0_value?: DecorationStyleInterface | undefined
    _letterSpacing_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing0_value?: number | string | undefined
    _textCase_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textCase0_value?: TextCase | undefined
    _baselineOffset_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _baselineOffset0_value?: number | string | undefined
    _copyOption_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption0_value?: CopyOptions | undefined
    _draggable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _draggable0_value?: boolean | undefined
    _textShadow_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textShadow0_value?: ShadowOptions | Array<ShadowOptions> | undefined
    _heightAdaptivePolicy_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _heightAdaptivePolicy0_value?: TextHeightAdaptivePolicy | undefined
    _textIndent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIndent0_value?: Length | undefined
    _wordBreak_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _wordBreak0_value?: WordBreak | undefined
    _lineBreakStrategy_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineBreakStrategy0_value?: LineBreakStrategy | undefined
    _onCopy_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy0_value?: ((value: string) => void) | undefined
    _caretColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretColor0_value?: ResourceColor | undefined
    _selectedBackgroundColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor0_value?: ResourceColor | undefined
    _ellipsisMode_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ellipsisMode0_value?: EllipsisMode | undefined
    _enableDataDetector_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDataDetector0_value?: boolean | undefined
    _dataDetectorConfig_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dataDetectorConfig0_value?: TextDataDetectorConfig | undefined
    _onTextSelectionChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTextSelectionChange0_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    _fontFeature_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFeature0_value?: string | undefined
    _marqueeOptions_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _marqueeOptions0_value?: TextMarqueeOptions | undefined
    _onMarqueeStateChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onMarqueeStateChange0_value?: ((value0: MarqueeState) => void) | undefined
    _privacySensitive_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive0_value?: boolean | undefined
    _textSelectable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textSelectable0_value?: TextSelectableMode | undefined
    _editMenuOptions_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions0_value?: EditMenuOptions | undefined
    _halfLeading_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _halfLeading0_value?: boolean | undefined
    _enableHapticFeedback_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback0_value?: boolean | undefined
    _font_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font0_value?: Font | undefined
    _font1_value?: FontSettingOptions | undefined
    _fontWeight_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight0_value?: number | FontWeight | string | undefined
    _fontWeight1_value?: FontSettingOptions | undefined
    _selection_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selection0_value?: number | undefined
    _selection1_value?: number | undefined
    _bindSelectionMenu_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSelectionMenu0_value?: TextSpanType | undefined
    _bindSelectionMenu1_value?: CustomBuilder | undefined
    _bindSelectionMenu2_value?: TextResponseType | undefined
    _bindSelectionMenu3_value?: SelectionMenuOptions | undefined

    applyNormalAttribute(instance: TextAttribute): void { }
    applyPressedAttribute(instance: TextAttribute): void { }
    applyFocusedAttribute(instance: TextAttribute): void { }
    applyDisabledAttribute(instance: TextAttribute): void { }
    applySelectedAttribute(instance: TextAttribute): void { }

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer: ArkTextPeer = value as ArkTextPeer
        if (this._fontColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor0_value as ResourceColor | undefined));
                    this._fontColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute(undefined);
                }
            }
        }
        if (this._fontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontSizeAttribute((this._fontSize0_value as number | string | Resource | undefined));
                    this._fontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontSizeAttribute(undefined);
                }
            }
        }
        if (this._minFontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minFontSizeAttribute((this._minFontSize0_value as number | string | Resource | undefined));
                    this._minFontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minFontSizeAttribute(undefined);
                }
            }
        }
        if (this._maxFontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontSize_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxFontSizeAttribute((this._maxFontSize0_value as number | string | Resource | undefined));
                    this._maxFontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontSize_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontSize_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxFontSizeAttribute(undefined);
                }
            }
        }
        if (this._minFontScale_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minFontScaleAttribute((this._minFontScale0_value as number | Resource | undefined));
                    this._minFontScale_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minFontScaleAttribute(undefined);
                }
            }
        }
        if (this._maxFontScale_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxFontScaleAttribute((this._maxFontScale0_value as number | Resource | undefined));
                    this._maxFontScale_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxFontScaleAttribute(undefined);
                }
            }
        }
        if (this._fontStyle_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontStyleAttribute((this._fontStyle0_value as FontStyle | undefined));
                    this._fontStyle_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontStyleAttribute(undefined);
                }
            }
        }
        if (this._lineSpacing_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineSpacing_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lineSpacingAttribute((this._lineSpacing0_value as LengthMetrics | undefined));
                    this._lineSpacing_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineSpacing_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineSpacing_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lineSpacingAttribute(undefined);
                }
            }
        }
        if (this._textAlign_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textAlign_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textAlignAttribute((this._textAlign0_value as TextAlign | undefined));
                    this._textAlign_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAlign_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAlign_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textAlignAttribute(undefined);
                }
            }
        }
        if (this._lineHeight_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineHeight_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lineHeightAttribute((this._lineHeight0_value as number | string | Resource | undefined));
                    this._lineHeight_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lineHeightAttribute(undefined);
                }
            }
        }
        if (this._textOverflow_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textOverflow_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textOverflowAttribute((this._textOverflow0_value as TextOverflowOptions | undefined));
                    this._textOverflow_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textOverflow_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textOverflow_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textOverflowAttribute(undefined);
                }
            }
        }
        if (this._fontFamily_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFamilyAttribute((this._fontFamily0_value as string | Resource | undefined));
                    this._fontFamily_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFamilyAttribute(undefined);
                }
            }
        }
        if (this._maxLines_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLines_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxLinesAttribute((this._maxLines0_value as number | undefined));
                    this._maxLines_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLines_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLines_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxLinesAttribute(undefined);
                }
            }
        }
        if (this._decoration_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._decoration_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.decorationAttribute((this._decoration0_value as DecorationStyleInterface | undefined));
                    this._decoration_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_flag = AttributeUpdaterFlag.INITIAL;
                    peer.decorationAttribute(undefined);
                }
            }
        }
        if (this._letterSpacing_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._letterSpacing_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.letterSpacingAttribute((this._letterSpacing0_value as number | string | undefined));
                    this._letterSpacing_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._letterSpacing_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._letterSpacing_flag = AttributeUpdaterFlag.INITIAL;
                    peer.letterSpacingAttribute(undefined);
                }
            }
        }
        if (this._textCase_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textCase_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textCaseAttribute((this._textCase0_value as TextCase | undefined));
                    this._textCase_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textCase_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textCase_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textCaseAttribute(undefined);
                }
            }
        }
        if (this._baselineOffset_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._baselineOffset_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.baselineOffsetAttribute((this._baselineOffset0_value as number | string | undefined));
                    this._baselineOffset_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._baselineOffset_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._baselineOffset_flag = AttributeUpdaterFlag.INITIAL;
                    peer.baselineOffsetAttribute(undefined);
                }
            }
        }
        if (this._copyOption_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOption_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.copyOptionAttribute((this._copyOption0_value as CopyOptions | undefined));
                    this._copyOption_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_flag = AttributeUpdaterFlag.INITIAL;
                    peer.copyOptionAttribute(undefined);
                }
            }
        }
        if (this._draggable_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._draggable_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.draggableAttribute((this._draggable0_value as boolean | undefined));
                    this._draggable_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._draggable_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._draggable_flag = AttributeUpdaterFlag.INITIAL;
                    peer.draggableAttribute(undefined);
                }
            }
        }
        if (this._textShadow_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textShadow_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textShadowAttribute((this._textShadow0_value as ShadowOptions | Array<ShadowOptions> | undefined));
                    this._textShadow_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textShadow_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textShadow_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textShadowAttribute(undefined);
                }
            }
        }
        if (this._heightAdaptivePolicy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._heightAdaptivePolicy_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.heightAdaptivePolicyAttribute((this._heightAdaptivePolicy0_value as TextHeightAdaptivePolicy | undefined));
                    this._heightAdaptivePolicy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._heightAdaptivePolicy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._heightAdaptivePolicy_flag = AttributeUpdaterFlag.INITIAL;
                    peer.heightAdaptivePolicyAttribute(undefined);
                }
            }
        }
        if (this._textIndent_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textIndent_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textIndentAttribute((this._textIndent0_value as Length | undefined));
                    this._textIndent_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIndent_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIndent_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textIndentAttribute(undefined);
                }
            }
        }
        if (this._wordBreak_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._wordBreak_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.wordBreakAttribute((this._wordBreak0_value as WordBreak | undefined));
                    this._wordBreak_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._wordBreak_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._wordBreak_flag = AttributeUpdaterFlag.INITIAL;
                    peer.wordBreakAttribute(undefined);
                }
            }
        }
        if (this._lineBreakStrategy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineBreakStrategy_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lineBreakStrategyAttribute((this._lineBreakStrategy0_value as LineBreakStrategy | undefined));
                    this._lineBreakStrategy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineBreakStrategy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineBreakStrategy_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lineBreakStrategyAttribute(undefined);
                }
            }
        }
        if (this._onCopy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCopy_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCopyAttribute((this._onCopy0_value as ((value: string) => void) | undefined));
                    this._onCopy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCopy_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCopy_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCopyAttribute(undefined);
                }
            }
        }
        if (this._caretColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._caretColor_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.caretColorAttribute((this._caretColor0_value as ResourceColor | undefined));
                    this._caretColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretColor_flag = AttributeUpdaterFlag.INITIAL;
                    peer.caretColorAttribute(undefined);
                }
            }
        }
        if (this._selectedBackgroundColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBackgroundColor_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedBackgroundColorAttribute((this._selectedBackgroundColor0_value as ResourceColor | undefined));
                    this._selectedBackgroundColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedBackgroundColorAttribute(undefined);
                }
            }
        }
        if (this._ellipsisMode_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._ellipsisMode_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.ellipsisModeAttribute((this._ellipsisMode0_value as EllipsisMode | undefined));
                    this._ellipsisMode_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._ellipsisMode_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._ellipsisMode_flag = AttributeUpdaterFlag.INITIAL;
                    peer.ellipsisModeAttribute(undefined);
                }
            }
        }
        if (this._enableDataDetector_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDataDetector_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableDataDetectorAttribute((this._enableDataDetector0_value as boolean | undefined));
                    this._enableDataDetector_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDataDetector_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDataDetector_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableDataDetectorAttribute(undefined);
                }
            }
        }
        if (this._dataDetectorConfig_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dataDetectorConfig_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dataDetectorConfigAttribute((this._dataDetectorConfig0_value as TextDataDetectorConfig | undefined));
                    this._dataDetectorConfig_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dataDetectorConfig_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dataDetectorConfig_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dataDetectorConfigAttribute(undefined);
                }
            }
        }
        if (this._onTextSelectionChange_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTextSelectionChange_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onTextSelectionChangeAttribute((this._onTextSelectionChange0_value as ((selectionStart: number,selectionEnd: number) => void) | undefined));
                    this._onTextSelectionChange_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTextSelectionChange_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTextSelectionChange_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onTextSelectionChangeAttribute(undefined);
                }
            }
        }
        if (this._fontFeature_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFeature_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFeatureAttribute((this._fontFeature0_value as string | undefined));
                    this._fontFeature_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFeature_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFeature_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFeatureAttribute(undefined);
                }
            }
        }
        if (this._marqueeOptions_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._marqueeOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.marqueeOptionsAttribute((this._marqueeOptions0_value as TextMarqueeOptions | undefined));
                    this._marqueeOptions_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._marqueeOptions_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._marqueeOptions_flag = AttributeUpdaterFlag.INITIAL;
                    peer.marqueeOptionsAttribute(undefined);
                }
            }
        }
        if (this._onMarqueeStateChange_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onMarqueeStateChange_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onMarqueeStateChangeAttribute((this._onMarqueeStateChange0_value as ((value0: MarqueeState) => void) | undefined));
                    this._onMarqueeStateChange_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onMarqueeStateChange_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onMarqueeStateChange_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onMarqueeStateChangeAttribute(undefined);
                }
            }
        }
        if (this._privacySensitive_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.privacySensitiveAttribute((this._privacySensitive0_value as boolean | undefined));
                    this._privacySensitive_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_flag = AttributeUpdaterFlag.INITIAL;
                    peer.privacySensitiveAttribute(undefined);
                }
            }
        }
        if (this._textSelectable_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textSelectable_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textSelectableAttribute((this._textSelectable0_value as TextSelectableMode | undefined));
                    this._textSelectable_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textSelectable_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textSelectable_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textSelectableAttribute(undefined);
                }
            }
        }
        if (this._editMenuOptions_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.editMenuOptionsAttribute((this._editMenuOptions0_value as EditMenuOptions | undefined));
                    this._editMenuOptions_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_flag = AttributeUpdaterFlag.INITIAL;
                    peer.editMenuOptionsAttribute(undefined);
                }
            }
        }
        if (this._halfLeading_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._halfLeading_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.halfLeadingAttribute((this._halfLeading0_value as boolean | undefined));
                    this._halfLeading_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._halfLeading_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._halfLeading_flag = AttributeUpdaterFlag.INITIAL;
                    peer.halfLeadingAttribute(undefined);
                }
            }
        }
        if (this._enableHapticFeedback_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableHapticFeedbackAttribute((this._enableHapticFeedback0_value as boolean | undefined));
                    this._enableHapticFeedback_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableHapticFeedbackAttribute(undefined);
                }
            }
        }
        if (this._font_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.font1Attribute((this._font0_value as Font | undefined), (this._font1_value as FontSettingOptions | undefined));
                    this._font_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_flag = AttributeUpdaterFlag.INITIAL;
                    peer.font1Attribute(undefined, undefined);
                }
            }
        }
        if (this._fontWeight_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontWeight1Attribute((this._fontWeight0_value as number | FontWeight | string | undefined), (this._fontWeight1_value as FontSettingOptions | undefined));
                    this._fontWeight_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontWeight1Attribute(undefined, undefined);
                }
            }
        }
        if (this._selection_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selection_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectionAttribute((this._selection0_value as number | undefined), (this._selection1_value as number | undefined));
                    this._selection_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selection_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selection_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectionAttribute(undefined, undefined);
                }
            }
        }
        if (this._bindSelectionMenu_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSelectionMenu_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.bindSelectionMenuAttribute((this._bindSelectionMenu0_value as TextSpanType | undefined), (this._bindSelectionMenu1_value as CustomBuilder | undefined), (this._bindSelectionMenu2_value as TextResponseType | undefined), (this._bindSelectionMenu3_value as SelectionMenuOptions | undefined));
                    this._bindSelectionMenu_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSelectionMenu_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSelectionMenu_flag = AttributeUpdaterFlag.INITIAL;
                    peer.bindSelectionMenuAttribute(undefined, undefined, undefined, undefined);
                }
            }
        }
    }
    mergeModifier(modifier: TextModifier): void {
        super.mergeModifier(modifier)
        if (modifier._fontColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor0_value);
                    break;
                }
                default: {
                    this.fontColor(undefined);
                }
            }
        }
        if (modifier._fontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize0_value);
                    break;
                }
                default: {
                    this.fontSize(undefined);
                }
            }
        }
        if (modifier._minFontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize0_value);
                    break;
                }
                default: {
                    this.minFontSize(undefined);
                }
            }
        }
        if (modifier._maxFontSize_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontSize_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontSize(modifier._maxFontSize0_value);
                    break;
                }
                default: {
                    this.maxFontSize(undefined);
                }
            }
        }
        if (modifier._minFontScale_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale0_value);
                    break;
                }
                default: {
                    this.minFontScale(undefined);
                }
            }
        }
        if (modifier._maxFontScale_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale0_value);
                    break;
                }
                default: {
                    this.maxFontScale(undefined);
                }
            }
        }
        if (modifier._fontStyle_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontStyle_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontStyle(modifier._fontStyle0_value);
                    break;
                }
                default: {
                    this.fontStyle(undefined);
                }
            }
        }
        if (modifier._lineSpacing_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineSpacing_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineSpacing(modifier._lineSpacing0_value);
                    break;
                }
                default: {
                    this.lineSpacing(undefined);
                }
            }
        }
        if (modifier._textAlign_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textAlign_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textAlign(modifier._textAlign0_value);
                    break;
                }
                default: {
                    this.textAlign(undefined);
                }
            }
        }
        if (modifier._lineHeight_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineHeight_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineHeight(modifier._lineHeight0_value);
                    break;
                }
                default: {
                    this.lineHeight(undefined);
                }
            }
        }
        if (modifier._textOverflow_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textOverflow_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textOverflow(modifier._textOverflow0_value);
                    break;
                }
                default: {
                    this.textOverflow(undefined);
                }
            }
        }
        if (modifier._fontFamily_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily0_value);
                    break;
                }
                default: {
                    this.fontFamily(undefined);
                }
            }
        }
        if (modifier._maxLines_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLines_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLines(modifier._maxLines0_value);
                    break;
                }
                default: {
                    this.maxLines(undefined);
                }
            }
        }
        if (modifier._decoration_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._decoration_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.decoration(modifier._decoration0_value);
                    break;
                }
                default: {
                    this.decoration(undefined);
                }
            }
        }
        if (modifier._letterSpacing_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._letterSpacing_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.letterSpacing(modifier._letterSpacing0_value);
                    break;
                }
                default: {
                    this.letterSpacing(undefined);
                }
            }
        }
        if (modifier._textCase_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textCase_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textCase(modifier._textCase0_value);
                    break;
                }
                default: {
                    this.textCase(undefined);
                }
            }
        }
        if (modifier._baselineOffset_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._baselineOffset_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.baselineOffset(modifier._baselineOffset0_value);
                    break;
                }
                default: {
                    this.baselineOffset(undefined);
                }
            }
        }
        if (modifier._copyOption_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOption_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOption(modifier._copyOption0_value);
                    break;
                }
                default: {
                    this.copyOption(undefined);
                }
            }
        }
        if (modifier._draggable_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._draggable_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.draggable(modifier._draggable0_value);
                    break;
                }
                default: {
                    this.draggable(undefined);
                }
            }
        }
        if (modifier._textShadow_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textShadow_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textShadow(modifier._textShadow0_value);
                    break;
                }
                default: {
                    this.textShadow(undefined);
                }
            }
        }
        if (modifier._heightAdaptivePolicy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._heightAdaptivePolicy_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.heightAdaptivePolicy(modifier._heightAdaptivePolicy0_value);
                    break;
                }
                default: {
                    this.heightAdaptivePolicy(undefined);
                }
            }
        }
        if (modifier._textIndent_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textIndent_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textIndent(modifier._textIndent0_value);
                    break;
                }
                default: {
                    this.textIndent(undefined);
                }
            }
        }
        if (modifier._wordBreak_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._wordBreak_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.wordBreak(modifier._wordBreak0_value);
                    break;
                }
                default: {
                    this.wordBreak(undefined);
                }
            }
        }
        if (modifier._lineBreakStrategy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineBreakStrategy_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineBreakStrategy(modifier._lineBreakStrategy0_value);
                    break;
                }
                default: {
                    this.lineBreakStrategy(undefined);
                }
            }
        }
        if (modifier._onCopy_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCopy_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCopy(modifier._onCopy0_value);
                    break;
                }
                default: {
                    this.onCopy(undefined);
                }
            }
        }
        if (modifier._caretColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._caretColor_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.caretColor(modifier._caretColor0_value);
                    break;
                }
                default: {
                    this.caretColor(undefined);
                }
            }
        }
        if (modifier._selectedBackgroundColor_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedBackgroundColor_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor0_value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor(undefined);
                }
            }
        }
        if (modifier._ellipsisMode_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._ellipsisMode_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.ellipsisMode(modifier._ellipsisMode0_value);
                    break;
                }
                default: {
                    this.ellipsisMode(undefined);
                }
            }
        }
        if (modifier._enableDataDetector_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDataDetector_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDataDetector(modifier._enableDataDetector0_value);
                    break;
                }
                default: {
                    this.enableDataDetector(undefined);
                }
            }
        }
        if (modifier._dataDetectorConfig_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dataDetectorConfig_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dataDetectorConfig(modifier._dataDetectorConfig0_value);
                    break;
                }
                default: {
                    this.dataDetectorConfig(undefined);
                }
            }
        }
        if (modifier._onTextSelectionChange_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTextSelectionChange_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTextSelectionChange(modifier._onTextSelectionChange0_value);
                    break;
                }
                default: {
                    this.onTextSelectionChange(undefined);
                }
            }
        }
        if (modifier._fontFeature_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFeature_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFeature(modifier._fontFeature0_value);
                    break;
                }
                default: {
                    this.fontFeature(undefined);
                }
            }
        }
        if (modifier._marqueeOptions_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._marqueeOptions_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.marqueeOptions(modifier._marqueeOptions0_value);
                    break;
                }
                default: {
                    this.marqueeOptions(undefined);
                }
            }
        }
        if (modifier._onMarqueeStateChange_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onMarqueeStateChange_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onMarqueeStateChange(modifier._onMarqueeStateChange0_value);
                    break;
                }
                default: {
                    this.onMarqueeStateChange(undefined);
                }
            }
        }
        if (modifier._privacySensitive_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive0_value);
                    break;
                }
                default: {
                    this.privacySensitive(undefined);
                }
            }
        }
        if (modifier._textSelectable_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textSelectable_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textSelectable(modifier._textSelectable0_value);
                    break;
                }
                default: {
                    this.textSelectable(undefined);
                }
            }
        }
        if (modifier._editMenuOptions_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMenuOptions_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions0_value);
                    break;
                }
                default: {
                    this.editMenuOptions(undefined);
                }
            }
        }
        if (modifier._halfLeading_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._halfLeading_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.halfLeading(modifier._halfLeading0_value);
                    break;
                }
                default: {
                    this.halfLeading(undefined);
                }
            }
        }
        if (modifier._enableHapticFeedback_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback0_value);
                    break;
                }
                default: {
                    this.enableHapticFeedback(undefined);
                }
            }
        }
        if (modifier._font_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font0_value, modifier._font1_value);
                    break;
                }
                default: {
                    this.font(undefined, undefined);
                }
            }
        }
        if (modifier._fontWeight_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight0_value, modifier._fontWeight1_value);
                    break;
                }
                default: {
                    this.fontWeight(undefined, undefined);
                }
            }
        }
        if (modifier._selection_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selection_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selection(modifier._selection0_value, modifier._selection1_value);
                    break;
                }
                default: {
                    this.selection(undefined, undefined);
                }
            }
        }
        if (modifier._bindSelectionMenu_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSelectionMenu_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu0_value, modifier._bindSelectionMenu1_value, modifier._bindSelectionMenu2_value, modifier._bindSelectionMenu3_value);
                    break;
                }
                default: {
                    this.bindSelectionMenu(undefined, undefined, undefined, undefined);
                }
            }
        }
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontColor0_value !== value || !Type.of(value).isPrimitive())
        {
            this._fontColor_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor0_value = value
        }
        else
        {
            this._fontColor_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: number | string | Resource | undefined): this {
        if (((this._fontSize_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontSize0_value !== value || !Type.of(value).isPrimitive())
        {
            this._fontSize_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize0_value = value
        }
        else
        {
            this._fontSize_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(value: number | string | Resource | undefined): this {
        if (((this._minFontSize_flag) == (AttributeUpdaterFlag.INITIAL)) || this._minFontSize0_value !== value || !Type.of(value).isPrimitive())
        {
            this._minFontSize_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize0_value = value
        }
        else
        {
            this._minFontSize_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        if (((this._maxFontSize_flag) == (AttributeUpdaterFlag.INITIAL)) || this._maxFontSize0_value !== value || !Type.of(value).isPrimitive())
        {
            this._maxFontSize_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontSize0_value = value
        }
        else
        {
            this._maxFontSize_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: number | Resource | undefined): this {
        if (((this._minFontScale_flag) == (AttributeUpdaterFlag.INITIAL)) || this._minFontScale0_value !== value || !Type.of(value).isPrimitive())
        {
            this._minFontScale_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale0_value = value
        }
        else
        {
            this._minFontScale_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: number | Resource | undefined): this {
        if (((this._maxFontScale_flag) == (AttributeUpdaterFlag.INITIAL)) || this._maxFontScale0_value !== value || !Type.of(value).isPrimitive())
        {
            this._maxFontScale_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale0_value = value
        }
        else
        {
            this._maxFontScale_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontStyle0_value !== value)
        {
            this._fontStyle_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle0_value = value
        }
        else
        {
            this._fontStyle_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        if (((this._lineSpacing_flag) == (AttributeUpdaterFlag.INITIAL)) || this._lineSpacing0_value !== value || !Type.of(value).isPrimitive())
        {
            this._lineSpacing_flag = AttributeUpdaterFlag.UPDATE
            this._lineSpacing0_value = value
        }
        else
        {
            this._lineSpacing_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._textAlign_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textAlign0_value !== value)
        {
            this._textAlign_flag = AttributeUpdaterFlag.UPDATE
            this._textAlign0_value = value
        }
        else
        {
            this._textAlign_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineHeight(value: number | string | Resource | undefined): this {
        if (((this._lineHeight_flag) == (AttributeUpdaterFlag.INITIAL)) || this._lineHeight0_value !== value || !Type.of(value).isPrimitive())
        {
            this._lineHeight_flag = AttributeUpdaterFlag.UPDATE
            this._lineHeight0_value = value
        }
        else
        {
            this._lineHeight_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        if (((this._textOverflow_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textOverflow0_value !== value || !Type.of(value).isPrimitive())
        {
            this._textOverflow_flag = AttributeUpdaterFlag.UPDATE
            this._textOverflow0_value = value
        }
        else
        {
            this._textOverflow_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontFamily0_value !== value || !Type.of(value).isPrimitive())
        {
            this._fontFamily_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily0_value = value
        }
        else
        {
            this._fontFamily_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLines(value: number | undefined): this {
        if (((this._maxLines_flag) == (AttributeUpdaterFlag.INITIAL)) || this._maxLines0_value !== value)
        {
            this._maxLines_flag = AttributeUpdaterFlag.UPDATE
            this._maxLines0_value = value
        }
        else
        {
            this._maxLines_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        if (((this._decoration_flag) == (AttributeUpdaterFlag.INITIAL)) || this._decoration0_value !== value || !Type.of(value).isPrimitive())
        {
            this._decoration_flag = AttributeUpdaterFlag.UPDATE
            this._decoration0_value = value
        }
        else
        {
            this._decoration_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    letterSpacing(value: number | string | undefined): this {
        if (((this._letterSpacing_flag) == (AttributeUpdaterFlag.INITIAL)) || this._letterSpacing0_value !== value)
        {
            this._letterSpacing_flag = AttributeUpdaterFlag.UPDATE
            this._letterSpacing0_value = value
        }
        else
        {
            this._letterSpacing_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textCase(value: TextCase | undefined): this {
        if (((this._textCase_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textCase0_value !== value)
        {
            this._textCase_flag = AttributeUpdaterFlag.UPDATE
            this._textCase0_value = value
        }
        else
        {
            this._textCase_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    baselineOffset(value: number | string | undefined): this {
        if (((this._baselineOffset_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._baselineOffset0_value) !== (value)))
        {
            this._baselineOffset_flag = AttributeUpdaterFlag.UPDATE
            this._baselineOffset0_value = value
        }
        else
        {
            this._baselineOffset_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_flag) == (AttributeUpdaterFlag.INITIAL)) || this._copyOption0_value !== value)
        {
            this._copyOption_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption0_value = value
        }
        else
        {
            this._copyOption_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._draggable_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable0_value) !== (value)))
        {
            this._draggable_flag = AttributeUpdaterFlag.UPDATE
            this._draggable0_value = value
        }
        else
        {
            this._draggable_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._textShadow_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textShadow0_value !== value || !Type.of(value).isPrimitive())
        {
            this._textShadow_flag = AttributeUpdaterFlag.UPDATE
            this._textShadow0_value = value
        }
        else
        {
            this._textShadow_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (((this._heightAdaptivePolicy_flag) == (AttributeUpdaterFlag.INITIAL)) || this._heightAdaptivePolicy0_value !== value)
        {
            this._heightAdaptivePolicy_flag = AttributeUpdaterFlag.UPDATE
            this._heightAdaptivePolicy0_value = value
        }
        else
        {
            this._heightAdaptivePolicy_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textIndent(value: Length | undefined): this {
        if (((this._textIndent_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textIndent0_value !== value || !Type.of(value).isPrimitive())
        {
            this._textIndent_flag = AttributeUpdaterFlag.UPDATE
            this._textIndent0_value = value
        }
        else
        {
            this._textIndent_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        if (((this._wordBreak_flag) == (AttributeUpdaterFlag.INITIAL)) || this._wordBreak0_value !== value)
        {
            this._wordBreak_flag = AttributeUpdaterFlag.UPDATE
            this._wordBreak0_value = value
        }
        else
        {
            this._wordBreak_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (((this._lineBreakStrategy_flag) == (AttributeUpdaterFlag.INITIAL)) || this._lineBreakStrategy0_value !== value)
        {
            this._lineBreakStrategy_flag = AttributeUpdaterFlag.UPDATE
            this._lineBreakStrategy0_value = value
        }
        else
        {
            this._lineBreakStrategy_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        if (((this._onCopy_flag) == (AttributeUpdaterFlag.INITIAL)) || this._onCopy0_value !== value || !Type.of(value).isPrimitive())
        {
            this._onCopy_flag = AttributeUpdaterFlag.UPDATE
            this._onCopy0_value = value
        }
        else
        {
            this._onCopy_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._caretColor_flag) == (AttributeUpdaterFlag.INITIAL)) || this._caretColor0_value !== value || !Type.of(value).isPrimitive())
        {
            this._caretColor_flag = AttributeUpdaterFlag.UPDATE
            this._caretColor0_value = value
        }
        else
        {
            this._caretColor_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_flag) == (AttributeUpdaterFlag.INITIAL)) || this._selectedBackgroundColor0_value !== value || !Type.of(value).isPrimitive())
        {
            this._selectedBackgroundColor_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor0_value = value
        }
        else
        {
            this._selectedBackgroundColor_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        if (((this._ellipsisMode_flag) == (AttributeUpdaterFlag.INITIAL)) || this._ellipsisMode0_value !== value)
        {
            this._ellipsisMode_flag = AttributeUpdaterFlag.UPDATE
            this._ellipsisMode0_value = value
        }
        else
        {
            this._ellipsisMode_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._enableDataDetector_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDataDetector0_value) !== (value)))
        {
            this._enableDataDetector_flag = AttributeUpdaterFlag.UPDATE
            this._enableDataDetector0_value = value
        }
        else
        {
            this._enableDataDetector_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._dataDetectorConfig_flag) == (AttributeUpdaterFlag.INITIAL)) || this._dataDetectorConfig0_value !== value || !Type.of(value).isPrimitive())
        {
            this._dataDetectorConfig_flag = AttributeUpdaterFlag.UPDATE
            this._dataDetectorConfig0_value = value
        }
        else
        {
            this._dataDetectorConfig_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        if (((this._onTextSelectionChange_flag) == (AttributeUpdaterFlag.INITIAL)) || this._onTextSelectionChange0_value !== value || !Type.of(value).isPrimitive())
        {
            this._onTextSelectionChange_flag = AttributeUpdaterFlag.UPDATE
            this._onTextSelectionChange0_value = value
        }
        else
        {
            this._onTextSelectionChange_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._fontFeature_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fontFeature0_value) !== (value)))
        {
            this._fontFeature_flag = AttributeUpdaterFlag.UPDATE
            this._fontFeature0_value = value
        }
        else
        {
            this._fontFeature_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (((this._marqueeOptions_flag) == (AttributeUpdaterFlag.INITIAL)) || this._marqueeOptions0_value !== value || !Type.of(value).isPrimitive())
        {
            this._marqueeOptions_flag = AttributeUpdaterFlag.UPDATE
            this._marqueeOptions0_value = value
        }
        else
        {
            this._marqueeOptions_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        if (((this._onMarqueeStateChange_flag) == (AttributeUpdaterFlag.INITIAL)) || this._onMarqueeStateChange0_value !== value || !Type.of(value).isPrimitive())
        {
            this._onMarqueeStateChange_flag = AttributeUpdaterFlag.UPDATE
            this._onMarqueeStateChange0_value = value
        }
        else
        {
            this._onMarqueeStateChange_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive0_value) !== (value)))
        {
            this._privacySensitive_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive0_value = value
        }
        else
        {
            this._privacySensitive_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        if (((this._textSelectable_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textSelectable0_value !== value)
        {
            this._textSelectable_flag = AttributeUpdaterFlag.UPDATE
            this._textSelectable0_value = value
        }
        else
        {
            this._textSelectable_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_flag) == (AttributeUpdaterFlag.INITIAL)) || this._editMenuOptions0_value !== value || !Type.of(value).isPrimitive())
        {
            this._editMenuOptions_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions0_value = value
        }
        else
        {
            this._editMenuOptions_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._halfLeading_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._halfLeading0_value) !== (value)))
        {
            this._halfLeading_flag = AttributeUpdaterFlag.UPDATE
            this._halfLeading0_value = value
        }
        else
        {
            this._halfLeading_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback0_value) !== (value)))
        {
            this._enableHapticFeedback_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback0_value = value
        }
        else
        {
            this._enableHapticFeedback_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        if (((this._font_flag) == (AttributeUpdaterFlag.INITIAL)) || this._font0_value !== fontValue || !Type.of(fontValue).isPrimitive() ||
            this._font1_value !== options || !Type.of(options).isPrimitive())
        {
            this._font_flag = AttributeUpdaterFlag.UPDATE
            this._font0_value = fontValue
            this._font1_value = options
        }
        else
        {
            this._font_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (((this._fontWeight_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontWeight0_value !== weight ||
            this._fontWeight1_value !== options || !Type.of(options).isPrimitive())
        {
            this._fontWeight_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight0_value = weight
            this._fontWeight1_value = options
        }
        else
        {
            this._fontWeight_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        if (((this._selection_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selection0_value) !== (selectionStart)) || ((this._selection1_value) !== (selectionEnd)))
        {
            this._selection_flag = AttributeUpdaterFlag.UPDATE
            this._selection0_value = selectionStart
            this._selection1_value = selectionEnd
        }
        else
        {
            this._selection_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._bindSelectionMenu_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._bindSelectionMenu0_value !== spanType ||
            this._bindSelectionMenu1_value !== content || !Type.of(content).isPrimitive() ||
            this._bindSelectionMenu2_value !== responseType ||
            this._bindSelectionMenu3_value !== options || !Type.of(options).isPrimitive())
        {
            this._bindSelectionMenu_flag = AttributeUpdaterFlag.UPDATE
            this._bindSelectionMenu0_value = spanType
            this._bindSelectionMenu1_value = content
            this._bindSelectionMenu2_value = responseType
            this._bindSelectionMenu3_value = options
        }
        else
        {
            this._bindSelectionMenu_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}