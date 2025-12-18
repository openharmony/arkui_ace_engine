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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTextPeer, TextOverflowOptions, TextMarqueeOptions, MarqueeState, TextAttribute, TextSpanType, TextResponseType } from './component/text'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, ShadowOptions, Callback as arkui_component_common_Callback } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, LengthMetrics as arkui_component_units_LengthMetrics, Length, Font as arkui_component_units_Font } from './component/units'
import { Color as arkui_component_enums_Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { DecorationStyleInterface } from './component/styledString'
import { TextDataDetectorConfig, EditMenuOptions, FontSettingOptions } from './component/textCommon'
import { CustomBuilder } from './component/builder'
import { SelectionMenuOptions } from './component/richEditor'
export class TextModifier extends CommonMethodModifier implements TextAttribute,AttributeModifier<TextAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextAttribute): void { }
    applyPressedAttribute(instance: TextAttribute): void { }
    applyFocusedAttribute(instance: TextAttribute): void { }
    applyDisabledAttribute(instance: TextAttribute): void { }
    applySelectedAttribute(instance: TextAttribute): void { }
    public _fontColor_0_0value?: ResourceColor | undefined
    public _fontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _minFontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _maxFontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _minFontScale_0_0value?: double | arkui_component_units_Resource | undefined
    public _maxFontScale_0_0value?: double | arkui_component_units_Resource | undefined
    public _fontStyle_0_0value?: FontStyle | undefined
    public _lineSpacing_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _textAlign_0_0value?: TextAlign | undefined
    public _lineHeight_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _textOverflow_0_0value?: TextOverflowOptions | undefined
    public _fontFamily_0_0value?: string | arkui_component_units_Resource | undefined
    public _maxLines_0_0value?: int32 | undefined
    public _decoration_0_0value?: DecorationStyleInterface | undefined
    public _letterSpacing_0_0value?: double | string | undefined
    public _textCase_0_0value?: TextCase | undefined
    public _baselineOffset_0_0value?: double | string | undefined
    public _copyOption_0_0value?: CopyOptions | undefined
    public _draggable_0_0value?: boolean | undefined
    public _textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    public _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    public _textIndent_0_0value?: Length | undefined
    public _wordBreak_0_0value?: WordBreak | undefined
    public _lineBreakStrategy_0_0value?: LineBreakStrategy | undefined
    public _onCopy_0_0value?: ((breakpoints: string) => void) | undefined
    public _caretColor_0_0value?: ResourceColor | undefined
    public _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    public _ellipsisMode_0_0value?: EllipsisMode | undefined
    public _enableDataDetector_0_0value?: boolean | undefined
    public _dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    public _onTextSelectionChange_0_0value?: ((first: int32,last: int32) => void) | undefined
    public _fontFeature_0_0value?: string | undefined
    public _marqueeOptions_0_0value?: TextMarqueeOptions | undefined
    public _onMarqueeStateChange_0_0value?: arkui_component_common_Callback<MarqueeState, void> | undefined
    public _privacySensitive_0_0value?: boolean | undefined
    public _textSelectable_0_0value?: TextSelectableMode | undefined
    public _editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _halfLeading_0_0value?: boolean | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _font_0_0value?: arkui_component_units_Font | undefined
    public _font_0_1value?: FontSettingOptions | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    public _fontWeight_0_1value?: FontSettingOptions | undefined
    public _selection_0_0value?: int32 | undefined
    public _selection_0_1value?: int32 | undefined
    public _bindSelectionMenu_0_0value?: TextSpanType | undefined
    public _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    public _bindSelectionMenu_0_2value?: TextResponseType | undefined
    public _bindSelectionMenu_0_3value?: SelectionMenuOptions | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTextPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setFontSizeAttribute((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setMinFontSizeAttribute((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setMaxFontSizeAttribute((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | arkui_component_units_Resource | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setMinFontScaleAttribute((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | arkui_component_units_Resource | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setMaxFontScaleAttribute((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setLineSpacingAttribute((this._lineSpacing_0_0value as arkui_component_units_LengthMetrics | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setLineSpacingAttribute((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setTextAlignAttribute((this._textAlign_0_0value as TextAlign | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setTextAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setLineHeightAttribute((this._lineHeight_0_0value as double | string | arkui_component_units_Resource | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setLineHeightAttribute((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setTextOverflowAttribute((this._textOverflow_0_0value as TextOverflowOptions | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setTextOverflowAttribute((undefined as TextOverflowOptions | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | arkui_component_units_Resource | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setFontFamilyAttribute((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setMaxLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setDecorationAttribute((this._decoration_0_0value as DecorationStyleInterface | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setDecorationAttribute((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setLetterSpacingAttribute((this._letterSpacing_0_0value as double | string | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setLetterSpacingAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setTextCaseAttribute((this._textCase_0_0value as TextCase | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setTextCaseAttribute((undefined as TextCase | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setBaselineOffsetAttribute((this._baselineOffset_0_0value as double | string | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setBaselineOffsetAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setTextShadowAttribute((this._textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setTextShadowAttribute((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setHeightAdaptivePolicyAttribute((this._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setTextIndentAttribute((this._textIndent_0_0value as Length | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setTextIndentAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setWordBreakAttribute((this._wordBreak_0_0value as WordBreak | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setWordBreakAttribute((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setLineBreakStrategyAttribute((this._lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setLineBreakStrategyAttribute((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setOnCopyAttribute((this._onCopy_0_0value as ((breakpoints: string) => void) | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setOnCopyAttribute((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setCaretColorAttribute((this._caretColor_0_0value as ResourceColor | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setCaretColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setEllipsisModeAttribute((this._ellipsisMode_0_0value as EllipsisMode | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setEllipsisModeAttribute((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setEnableDataDetectorAttribute((this._enableDataDetector_0_0value as boolean | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setEnableDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setDataDetectorConfigAttribute((this._dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setDataDetectorConfigAttribute((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setOnTextSelectionChangeAttribute((this._onTextSelectionChange_0_0value as ((first: int32,last: int32) => void) | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setOnTextSelectionChangeAttribute((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setFontFeatureAttribute((this._fontFeature_0_0value as string | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setFontFeatureAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setMarqueeOptionsAttribute((this._marqueeOptions_0_0value as TextMarqueeOptions | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setMarqueeOptionsAttribute((undefined as TextMarqueeOptions | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setOnMarqueeStateChangeAttribute((this._onMarqueeStateChange_0_0value as arkui_component_common_Callback<MarqueeState, void> | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setOnMarqueeStateChangeAttribute((undefined as arkui_component_common_Callback<MarqueeState, void> | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1: {
                    peer.setTextSelectableAttribute((this._textSelectable_0_0value as TextSelectableMode | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setTextSelectableAttribute((undefined as TextSelectableMode | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1: {
                    peer.setHalfLeadingAttribute((this._halfLeading_0_0value as boolean | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setHalfLeadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1: {
                    peer.setFontAttribute((this._font_0_0value as arkui_component_units_Font | undefined), (this._font_0_1value as FontSettingOptions | undefined | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setFontAttribute((undefined as arkui_component_units_Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
    }
    applyModifierPatch2(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined), (this._fontWeight_0_1value as FontSettingOptions | undefined | undefined));
                    flagArray[40] = 2;
                    break;
                }
                case 3: {
                    flagArray[40] = 2;
                    break;
                }
                default: {
                    flagArray[40] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1: {
                    peer.setSelectionAttribute((this._selection_0_0value as int32 | undefined), (this._selection_0_1value as int32 | undefined));
                    flagArray[41] = 2;
                    break;
                }
                case 3: {
                    flagArray[41] = 2;
                    break;
                }
                default: {
                    flagArray[41] = 0;
                    peer.setSelectionAttribute((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as TextSpanType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as TextResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptions | undefined | undefined));
                    flagArray[42] = 2;
                    break;
                }
                case 3: {
                    flagArray[42] = 2;
                    break;
                }
                default: {
                    flagArray[42] = 0;
                    peer.setBindSelectionMenuAttribute((undefined as TextSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as TextResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
    }
    mergeModifier0(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.lineSpacing(modifier._lineSpacing_0_0value);
                    break;
                }
                default: {
                    this.lineSpacing((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.textAlign(modifier._textAlign_0_0value);
                    break;
                }
                default: {
                    this.textAlign((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.lineHeight(modifier._lineHeight_0_0value);
                    break;
                }
                default: {
                    this.lineHeight((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.textOverflow(modifier._textOverflow_0_0value);
                    break;
                }
                default: {
                    this.textOverflow((undefined as TextOverflowOptions | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.decoration(modifier._decoration_0_0value);
                    break;
                }
                default: {
                    this.decoration((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.letterSpacing(modifier._letterSpacing_0_0value);
                    break;
                }
                default: {
                    this.letterSpacing((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.textCase(modifier._textCase_0_0value);
                    break;
                }
                default: {
                    this.textCase((undefined as TextCase | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.baselineOffset(modifier._baselineOffset_0_0value);
                    break;
                }
                default: {
                    this.baselineOffset((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.textShadow(modifier._textShadow_0_0value);
                    break;
                }
                default: {
                    this.textShadow((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.heightAdaptivePolicy(modifier._heightAdaptivePolicy_0_0value);
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.textIndent(modifier._textIndent_0_0value);
                    break;
                }
                default: {
                    this.textIndent((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.wordBreak(modifier._wordBreak_0_0value);
                    break;
                }
                default: {
                    this.wordBreak((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.lineBreakStrategy(modifier._lineBreakStrategy_0_0value);
                    break;
                }
                default: {
                    this.lineBreakStrategy((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.caretColor(modifier._caretColor_0_0value);
                    break;
                }
                default: {
                    this.caretColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.ellipsisMode(modifier._ellipsisMode_0_0value);
                    break;
                }
                default: {
                    this.ellipsisMode((undefined as EllipsisMode | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.enableDataDetector(modifier._enableDataDetector_0_0value);
                    break;
                }
                default: {
                    this.enableDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.dataDetectorConfig(modifier._dataDetectorConfig_0_0value);
                    break;
                }
                default: {
                    this.dataDetectorConfig((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.onTextSelectionChange(modifier._onTextSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.fontFeature(modifier._fontFeature_0_0value);
                    break;
                }
                default: {
                    this.fontFeature((undefined as string | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.marqueeOptions(modifier._marqueeOptions_0_0value);
                    break;
                }
                default: {
                    this.marqueeOptions((undefined as TextMarqueeOptions | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.onMarqueeStateChange(modifier._onMarqueeStateChange_0_0value);
                    break;
                }
                default: {
                    this.onMarqueeStateChange((undefined as arkui_component_common_Callback<MarqueeState, void> | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1:
                case 3: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1:
                case 3: {
                    this.textSelectable(modifier._textSelectable_0_0value);
                    break;
                }
                default: {
                    this.textSelectable((undefined as TextSelectableMode | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1:
                case 3: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1:
                case 3: {
                    this.halfLeading(modifier._halfLeading_0_0value);
                    break;
                }
                default: {
                    this.halfLeading((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1:
                case 3: {
                    this.font(modifier._font_0_0value, modifier._font_0_1value);
                    break;
                }
                default: {
                    this.font((undefined as arkui_component_units_Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier2(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1:
                case 3: {
                    this.fontWeight(modifier._fontWeight_0_0value, modifier._fontWeight_0_1value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1:
                case 3: {
                    this.selection(modifier._selection_0_0value, modifier._selection_0_1value);
                    break;
                }
                default: {
                    this.selection((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1:
                case 3: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu_0_0value, modifier._bindSelectionMenu_0_1value, modifier._bindSelectionMenu_0_2value, modifier._bindSelectionMenu_0_3value);
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as TextSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as TextResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    fontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    minFontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._minFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    maxFontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._maxFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    minFontScale(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    maxFontScale(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    lineSpacing(value: arkui_component_units_LengthMetrics | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._lineSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._textAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    lineHeight(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._lineHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._textOverflow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    fontFamily(value: string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    maxLines(value: int32 | undefined): this {
        if (((this._flagArray[12]) == (0)) || ((this._maxLines_0_0value) !== (value))) {
            this._flagArray[12] = 1
            this._maxLines_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._decoration_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    letterSpacing(value: double | string | undefined): this {
        if (((this._flagArray[14]) == (0)) || ((this._letterSpacing_0_0value) !== (value))) {
            this._flagArray[14] = 1
            this._letterSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    textCase(value: TextCase | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._textCase_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    baselineOffset(value: double | string | undefined): this {
        if (((this._flagArray[16]) == (0)) || ((this._baselineOffset_0_0value) !== (value))) {
            this._flagArray[16] = 1
            this._baselineOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._copyOption_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._flagArray[18]) == (0)) || ((this._draggable_0_0value) !== (value))) {
            this._flagArray[18] = 1
            this._draggable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._textShadow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._heightAdaptivePolicy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    textIndent(value: Length | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._textIndent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._wordBreak_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._lineBreakStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._onCopy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._caretColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true)) {
            this._flagArray[27] = 1
            this._ellipsisMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._flagArray[28]) == (0)) || ((this._enableDataDetector_0_0value) !== (value))) {
            this._flagArray[28] = 1
            this._enableDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true)) {
            this._flagArray[29] = 1
            this._dataDetectorConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    onTextSelectionChange(value: ((first: int32,last: int32) => void) | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true)) {
            this._flagArray[30] = 1
            this._onTextSelectionChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._flagArray[31]) == (0)) || ((this._fontFeature_0_0value) !== (value))) {
            this._flagArray[31] = 1
            this._fontFeature_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._marqueeOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    onMarqueeStateChange(value: arkui_component_common_Callback<MarqueeState, void> | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true)) {
            this._flagArray[33] = 1
            this._onMarqueeStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._flagArray[34]) == (0)) || ((this._privacySensitive_0_0value) !== (value))) {
            this._flagArray[34] = 1
            this._privacySensitive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[34] = 3
        }
        return this
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        if (((this._flagArray[35]) == (0)) || (true)) {
            this._flagArray[35] = 1
            this._textSelectable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[35] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true)) {
            this._flagArray[36] = 1
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[36] = 3
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._flagArray[37]) == (0)) || ((this._halfLeading_0_0value) !== (value))) {
            this._flagArray[37] = 1
            this._halfLeading_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[37] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[38]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[38] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[38] = 3
        }
        return this
    }
    font(fontValue: arkui_component_units_Font | undefined, options?: FontSettingOptions): this {
        if (((this._flagArray[39]) == (0)) || (true) || (true)) {
            this._flagArray[39] = 1
            this._font_0_0value = fontValue
            this._font_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[39] = 3
        }
        return this
    }
    fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (((this._flagArray[40]) == (0)) || (true) || (true)) {
            this._flagArray[40] = 1
            this._fontWeight_0_0value = weight
            this._fontWeight_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[40] = 3
        }
        return this
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        if (((this._flagArray[41]) == (0)) || ((this._selection_0_0value) !== (selectionStart)) || ((this._selection_0_1value) !== (selectionEnd))) {
            this._flagArray[41] = 1
            this._selection_0_0value = selectionStart
            this._selection_0_1value = selectionEnd
            this._state.fireChange()
        } else {
            this._flagArray[41] = 3
        }
        return this
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._flagArray[42]) == (0)) || (true) || (true) || (true) || (true)) {
            this._flagArray[42] = 1
            this._bindSelectionMenu_0_0value = spanType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else {
            this._flagArray[42] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
