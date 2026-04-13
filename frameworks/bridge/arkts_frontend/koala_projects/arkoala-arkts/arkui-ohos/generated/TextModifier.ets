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
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTextPeer, TextOverflowOptions, TextMarqueeOptions, MarqueeState, TextAttribute, TextSpanType, TextResponseType } from './component/text'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, ShadowOptions, Callback as arkui_component_common_Callback } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, LengthMetrics as arkui_component_units_LengthMetrics, Font as arkui_component_units_Font, ResourceStr } from './component/units'
import { Color as arkui_component_enums_Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { DecorationStyleInterface } from './component/styledString'
import { TextDataDetectorConfig, EditMenuOptions, ShaderStyle, TextVerticalAlign, ContentTransition, TextContentAlign, SelectedDragPreviewStyle, TextDirection, FontSettingOptions, LineSpacingOptions } from './component/textCommon'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from 'arkui.Graphics'
import { CustomBuilder } from './component/builder'
import { SelectionMenuOptions } from './component/richEditor'
export class TextModifier extends CommonMethodModifier implements TextAttribute,AttributeModifier<TextAttribute> {
    private _Text_addr: ArrayBuffer = new ArrayBuffer(4096);
    private _Text_flagArray: Uint8Array = new Uint8Array(this._Text_addr);
    constructor() {
        super();
        this._Text_flagArray.fill(0);
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextAttribute): void { }
    applyPressedAttribute(instance: TextAttribute): void { }
    applyFocusedAttribute(instance: TextAttribute): void { }
    applyDisabledAttribute(instance: TextAttribute): void { }
    applySelectedAttribute(instance: TextAttribute): void { }
    public _Text_fontColor_0_0value?: ResourceColor | undefined
    public _Text_fontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _Text_minFontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _Text_maxFontSize_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _Text_minFontScale_0_0value?: double | arkui_component_units_Resource | undefined
    public _Text_maxFontScale_0_0value?: double | arkui_component_units_Resource | undefined
    public _Text_fontStyle_0_0value?: FontStyle | undefined
    public _Text_textAlign_0_0value?: TextAlign | undefined
    public _Text_lineHeight_0_0value?: double | string | arkui_component_units_Resource | undefined
    public _Text_textOverflow_0_0value?: TextOverflowOptions | undefined
    public _Text_fontFamily_0_0value?: string | arkui_component_units_Resource | undefined
    public _Text_maxLines_0_0value?: int32 | undefined
    public _Text_decoration_0_0value?: DecorationStyleInterface | undefined
    public _Text_letterSpacing_0_0value?: double | string | undefined
    public _Text_textCase_0_0value?: TextCase | undefined
    public _Text_baselineOffset_0_0value?: double | string | undefined
    public _Text_copyOption_0_0value?: CopyOptions | undefined
    public _Text_draggable_0_0value?: boolean | undefined
    public _Text_textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    public _Text_heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    public _Text_textIndent_0_0value?: Length | undefined
    public _Text_wordBreak_0_0value?: WordBreak | undefined
    public _Text_lineBreakStrategy_0_0value?: LineBreakStrategy | undefined
    public _Text_onCopy_0_0value?: ((breakpoints: string) => void) | undefined
    public _Text_onWillCopy_0_0value?: arkui_component_common_Callback<string, boolean> | undefined
    public _Text_caretColor_0_0value?: ResourceColor | undefined
    public _Text_selectedBackgroundColor_0_0value?: ResourceColor | undefined
    public _Text_ellipsisMode_0_0value?: EllipsisMode | undefined
    public _Text_enableDataDetector_0_0value?: boolean | undefined
    public _Text_dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    public _Text_onTextSelectionChange_0_0value?: ((first: int32,last: int32) => void) | undefined
    public _Text_fontFeature_0_0value?: string | undefined
    public _Text_marqueeOptions_0_0value?: TextMarqueeOptions | undefined
    public _Text_onMarqueeStateChange_0_0value?: arkui_component_common_Callback<MarqueeState, void> | undefined
    public _Text_privacySensitive_0_0value?: boolean | undefined
    public _Text_textSelectable_0_0value?: TextSelectableMode | undefined
    public _Text_editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _Text_halfLeading_0_0value?: boolean | undefined
    public _Text_enableHapticFeedback_0_0value?: boolean | undefined
    public _Text_includeFontPadding_0_0value?: boolean | undefined
    public _Text_fallbackLineSpacing_0_0value?: boolean | undefined
    public _Text_optimizeTrailingSpace_0_0value?: boolean | undefined
    public _Text_shaderStyle_0_0value?: ShaderStyle | undefined
    public _Text_enableAutoSpacing_0_0value?: boolean | undefined
    public _Text_textVerticalAlign_0_0value?: TextVerticalAlign | undefined
    public _Text_contentTransition_0_0value?: ContentTransition | undefined
    public _Text_textContentAlign_0_0value?: TextContentAlign | undefined
    public _Text_minLines_0_0value?: int32 | undefined
    public _Text_minLineHeight_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _Text_maxLineHeight_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _Text_lineHeightMultiple_0_0value?: double | undefined
    public _Text_enableSelectedDataDetector_0_0value?: boolean | undefined
    public _Text_compressLeadingPunctuation_0_0value?: boolean | undefined
    public _Text_selectedDragPreviewStyle_0_0value?: SelectedDragPreviewStyle | undefined
    public _Text_textDirection_0_0value?: TextDirection | undefined
    public _Text_orphanCharOptimization_0_0value?: boolean | undefined
    public _Text_font_0_0value?: arkui_component_units_Font | undefined
    public _Text_font_0_1value?: FontSettingOptions | undefined
    public _Text_fontWeight_0_0value?: int32 | FontWeight | ResourceStr | undefined
    public _Text_fontWeight_0_1value?: FontSettingOptions | undefined
    public _Text_lineSpacing_0_0value?: arkui_component_units_LengthMetrics | undefined
    public _Text_lineSpacing_0_1value?: LineSpacingOptions | undefined
    public _Text_selection_0_0value?: int32 | undefined
    public _Text_selection_0_1value?: int32 | undefined
    public _Text_bindSelectionMenu_0_0value?: TextSpanType | undefined
    public _Text_bindSelectionMenu_0_1value?: CustomBuilder | undefined
    public _Text_bindSelectionMenu_0_2value?: TextResponseType | undefined
    public _Text_bindSelectionMenu_0_3value?: SelectionMenuOptions | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTextPeer;
        const flagArray = this._Text_flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
        this.applyModifierPatch3(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setFontColorAttribute((this._Text_fontColor_0_0value as ResourceColor | undefined));
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
                    peer.setFontSizeAttribute((this._Text_fontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    peer.setMinFontSizeAttribute((this._Text_minFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    peer.setMaxFontSizeAttribute((this._Text_maxFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    peer.setMinFontScaleAttribute((this._Text_minFontScale_0_0value as double | arkui_component_units_Resource | undefined));
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
                    peer.setMaxFontScaleAttribute((this._Text_maxFontScale_0_0value as double | arkui_component_units_Resource | undefined));
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
                    peer.setFontStyleAttribute((this._Text_fontStyle_0_0value as FontStyle | undefined));
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
                    peer.setTextAlignAttribute((this._Text_textAlign_0_0value as TextAlign | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setTextAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setLineHeightAttribute((this._Text_lineHeight_0_0value as double | string | arkui_component_units_Resource | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setLineHeightAttribute((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setTextOverflowAttribute((this._Text_textOverflow_0_0value as TextOverflowOptions | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setTextOverflowAttribute((undefined as TextOverflowOptions | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._Text_fontFamily_0_0value as string | arkui_component_units_Resource | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setFontFamilyAttribute((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setMaxLinesAttribute((this._Text_maxLines_0_0value as int32 | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setMaxLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setDecorationAttribute((this._Text_decoration_0_0value as DecorationStyleInterface | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setDecorationAttribute((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setLetterSpacingAttribute((this._Text_letterSpacing_0_0value as double | string | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setLetterSpacingAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setTextCaseAttribute((this._Text_textCase_0_0value as TextCase | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setTextCaseAttribute((undefined as TextCase | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setBaselineOffsetAttribute((this._Text_baselineOffset_0_0value as double | string | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setBaselineOffsetAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setCopyOptionAttribute((this._Text_copyOption_0_0value as CopyOptions | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setDraggableAttribute((this._Text_draggable_0_0value as boolean | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setTextShadowAttribute((this._Text_textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setTextShadowAttribute((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setHeightAdaptivePolicyAttribute((this._Text_heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setTextIndentAttribute((this._Text_textIndent_0_0value as Length | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setTextIndentAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setWordBreakAttribute((this._Text_wordBreak_0_0value as WordBreak | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setWordBreakAttribute((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setLineBreakStrategyAttribute((this._Text_lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setLineBreakStrategyAttribute((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setOnCopyAttribute((this._Text_onCopy_0_0value as ((breakpoints: string) => void) | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setOnCopyAttribute((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setOnWillCopyAttribute((this._Text_onWillCopy_0_0value as arkui_component_common_Callback<string, boolean> | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setOnWillCopyAttribute((undefined as arkui_component_common_Callback<string, boolean> | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setCaretColorAttribute((this._Text_caretColor_0_0value as ResourceColor | undefined));
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
                    peer.setSelectedBackgroundColorAttribute((this._Text_selectedBackgroundColor_0_0value as ResourceColor | undefined));
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
                    peer.setEllipsisModeAttribute((this._Text_ellipsisMode_0_0value as EllipsisMode | undefined));
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
                    peer.setEnableDataDetectorAttribute((this._Text_enableDataDetector_0_0value as boolean | undefined));
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
                    peer.setDataDetectorConfigAttribute((this._Text_dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
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
                    peer.setOnTextSelectionChangeAttribute((this._Text_onTextSelectionChange_0_0value as ((first: int32,last: int32) => void) | undefined));
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
                    peer.setFontFeatureAttribute((this._Text_fontFeature_0_0value as string | undefined));
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
                    peer.setMarqueeOptionsAttribute((this._Text_marqueeOptions_0_0value as TextMarqueeOptions | undefined));
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
                    peer.setOnMarqueeStateChangeAttribute((this._Text_onMarqueeStateChange_0_0value as arkui_component_common_Callback<MarqueeState, void> | undefined));
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
                    peer.setPrivacySensitiveAttribute((this._Text_privacySensitive_0_0value as boolean | undefined));
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
                    peer.setTextSelectableAttribute((this._Text_textSelectable_0_0value as TextSelectableMode | undefined));
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
                    peer.setEditMenuOptionsAttribute((this._Text_editMenuOptions_0_0value as EditMenuOptions | undefined));
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
                    peer.setHalfLeadingAttribute((this._Text_halfLeading_0_0value as boolean | undefined));
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
                    peer.setEnableHapticFeedbackAttribute((this._Text_enableHapticFeedback_0_0value as boolean | undefined));
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
                    peer.setIncludeFontPaddingAttribute((this._Text_includeFontPadding_0_0value as boolean | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setIncludeFontPaddingAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch2(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1: {
                    peer.setFallbackLineSpacingAttribute((this._Text_fallbackLineSpacing_0_0value as boolean | undefined));
                    flagArray[40] = 2;
                    break;
                }
                case 3: {
                    flagArray[40] = 2;
                    break;
                }
                default: {
                    flagArray[40] = 0;
                    peer.setFallbackLineSpacingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1: {
                    peer.setOptimizeTrailingSpaceAttribute((this._Text_optimizeTrailingSpace_0_0value as boolean | undefined));
                    flagArray[41] = 2;
                    break;
                }
                case 3: {
                    flagArray[41] = 2;
                    break;
                }
                default: {
                    flagArray[41] = 0;
                    peer.setOptimizeTrailingSpaceAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1: {
                    peer.setShaderStyleAttribute((this._Text_shaderStyle_0_0value as ShaderStyle | undefined));
                    flagArray[42] = 2;
                    break;
                }
                case 3: {
                    flagArray[42] = 2;
                    break;
                }
                default: {
                    flagArray[42] = 0;
                    peer.setShaderStyleAttribute((undefined as ShaderStyle | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1: {
                    peer.setEnableAutoSpacingAttribute((this._Text_enableAutoSpacing_0_0value as boolean | undefined));
                    flagArray[43] = 2;
                    break;
                }
                case 3: {
                    flagArray[43] = 2;
                    break;
                }
                default: {
                    flagArray[43] = 0;
                    peer.setEnableAutoSpacingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1: {
                    peer.setTextVerticalAlignAttribute((this._Text_textVerticalAlign_0_0value as TextVerticalAlign | undefined));
                    flagArray[44] = 2;
                    break;
                }
                case 3: {
                    flagArray[44] = 2;
                    break;
                }
                default: {
                    flagArray[44] = 0;
                    peer.setTextVerticalAlignAttribute((undefined as TextVerticalAlign | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1: {
                    peer.setContentTransitionAttribute((this._Text_contentTransition_0_0value as ContentTransition | undefined));
                    flagArray[45] = 2;
                    break;
                }
                case 3: {
                    flagArray[45] = 2;
                    break;
                }
                default: {
                    flagArray[45] = 0;
                    peer.setContentTransitionAttribute((undefined as ContentTransition | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1: {
                    peer.setTextContentAlignAttribute((this._Text_textContentAlign_0_0value as TextContentAlign | undefined));
                    flagArray[46] = 2;
                    break;
                }
                case 3: {
                    flagArray[46] = 2;
                    break;
                }
                default: {
                    flagArray[46] = 0;
                    peer.setTextContentAlignAttribute((undefined as TextContentAlign | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1: {
                    peer.setMinLinesAttribute((this._Text_minLines_0_0value as int32 | undefined));
                    flagArray[47] = 2;
                    break;
                }
                case 3: {
                    flagArray[47] = 2;
                    break;
                }
                default: {
                    flagArray[47] = 0;
                    peer.setMinLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1: {
                    peer.setMinLineHeightAttribute((this._Text_minLineHeight_0_0value as arkui_component_units_LengthMetrics | undefined));
                    flagArray[48] = 2;
                    break;
                }
                case 3: {
                    flagArray[48] = 2;
                    break;
                }
                default: {
                    flagArray[48] = 0;
                    peer.setMinLineHeightAttribute((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1: {
                    peer.setMaxLineHeightAttribute((this._Text_maxLineHeight_0_0value as arkui_component_units_LengthMetrics | undefined));
                    flagArray[49] = 2;
                    break;
                }
                case 3: {
                    flagArray[49] = 2;
                    break;
                }
                default: {
                    flagArray[49] = 0;
                    peer.setMaxLineHeightAttribute((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1: {
                    peer.setLineHeightMultipleAttribute((this._Text_lineHeightMultiple_0_0value as double | undefined));
                    flagArray[50] = 2;
                    break;
                }
                case 3: {
                    flagArray[50] = 2;
                    break;
                }
                default: {
                    flagArray[50] = 0;
                    peer.setLineHeightMultipleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1: {
                    peer.setEnableSelectedDataDetectorAttribute((this._Text_enableSelectedDataDetector_0_0value as boolean | undefined));
                    flagArray[51] = 2;
                    break;
                }
                case 3: {
                    flagArray[51] = 2;
                    break;
                }
                default: {
                    flagArray[51] = 0;
                    peer.setEnableSelectedDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1: {
                    peer.setCompressLeadingPunctuationAttribute((this._Text_compressLeadingPunctuation_0_0value as boolean | undefined));
                    flagArray[52] = 2;
                    break;
                }
                case 3: {
                    flagArray[52] = 2;
                    break;
                }
                default: {
                    flagArray[52] = 0;
                    peer.setCompressLeadingPunctuationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1: {
                    peer.setSelectedDragPreviewStyleAttribute((this._Text_selectedDragPreviewStyle_0_0value as SelectedDragPreviewStyle | undefined));
                    flagArray[53] = 2;
                    break;
                }
                case 3: {
                    flagArray[53] = 2;
                    break;
                }
                default: {
                    flagArray[53] = 0;
                    peer.setSelectedDragPreviewStyleAttribute((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1: {
                    peer.setTextDirectionAttribute((this._Text_textDirection_0_0value as TextDirection | undefined));
                    flagArray[54] = 2;
                    break;
                }
                case 3: {
                    flagArray[54] = 2;
                    break;
                }
                default: {
                    flagArray[54] = 0;
                    peer.setTextDirectionAttribute((undefined as TextDirection | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1: {
                    peer.setOrphanCharOptimizationAttribute((this._Text_orphanCharOptimization_0_0value as boolean | undefined));
                    flagArray[55] = 2;
                    break;
                }
                case 3: {
                    flagArray[55] = 2;
                    break;
                }
                default: {
                    flagArray[55] = 0;
                    peer.setOrphanCharOptimizationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1: {
                    peer.setFontAttribute((this._Text_font_0_0value as arkui_component_units_Font | undefined), (this._Text_font_0_1value as FontSettingOptions | undefined | undefined));
                    flagArray[56] = 2;
                    break;
                }
                case 3: {
                    flagArray[56] = 2;
                    break;
                }
                default: {
                    flagArray[56] = 0;
                    peer.setFontAttribute((undefined as arkui_component_units_Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1: {
                    peer.setFontWeightAttribute((this._Text_fontWeight_0_0value as int32 | FontWeight | ResourceStr | undefined), (this._Text_fontWeight_0_1value as FontSettingOptions | undefined | undefined));
                    flagArray[57] = 2;
                    break;
                }
                case 3: {
                    flagArray[57] = 2;
                    break;
                }
                default: {
                    flagArray[57] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | ResourceStr | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1: {
                    peer.setLineSpacingAttribute((this._Text_lineSpacing_0_0value as arkui_component_units_LengthMetrics | undefined), (this._Text_lineSpacing_0_1value as LineSpacingOptions | undefined));
                    flagArray[58] = 2;
                    break;
                }
                case 3: {
                    flagArray[58] = 2;
                    break;
                }
                default: {
                    flagArray[58] = 0;
                    peer.setLineSpacingAttribute((undefined as arkui_component_units_LengthMetrics | undefined), (undefined as LineSpacingOptions | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1: {
                    peer.setSelectionAttribute((this._Text_selection_0_0value as int32 | undefined), (this._Text_selection_0_1value as int32 | undefined));
                    flagArray[59] = 2;
                    break;
                }
                case 3: {
                    flagArray[59] = 2;
                    break;
                }
                default: {
                    flagArray[59] = 0;
                    peer.setSelectionAttribute((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    applyModifierPatch3(peer: ArkTextPeer, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute((this._Text_bindSelectionMenu_0_0value as TextSpanType | undefined), (this._Text_bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._Text_bindSelectionMenu_0_2value as TextResponseType | undefined), (this._Text_bindSelectionMenu_0_3value as SelectionMenuOptions | undefined | undefined));
                    flagArray[60] = 2;
                    break;
                }
                case 3: {
                    flagArray[60] = 2;
                    break;
                }
                default: {
                    flagArray[60] = 0;
                    peer.setBindSelectionMenuAttribute((undefined as TextSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as TextResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._Text_flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
        this.mergeModifier3(modifier, flagArray);
    }
    mergeModifier0(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.fontColor((modifier._Text_fontColor_0_0value as ResourceColor | undefined));
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
                    this.fontSize((modifier._Text_fontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    this.minFontSize((modifier._Text_minFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    this.maxFontSize((modifier._Text_maxFontSize_0_0value as double | string | arkui_component_units_Resource | undefined));
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
                    this.minFontScale((modifier._Text_minFontScale_0_0value as double | arkui_component_units_Resource | undefined));
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
                    this.maxFontScale((modifier._Text_maxFontScale_0_0value as double | arkui_component_units_Resource | undefined));
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
                    this.fontStyle((modifier._Text_fontStyle_0_0value as FontStyle | undefined));
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
                    this.textAlign((modifier._Text_textAlign_0_0value as TextAlign | undefined));
                    break;
                }
                default: {
                    this.textAlign((undefined as TextAlign | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.lineHeight((modifier._Text_lineHeight_0_0value as double | string | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.lineHeight((undefined as double | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.textOverflow((modifier._Text_textOverflow_0_0value as TextOverflowOptions | undefined));
                    break;
                }
                default: {
                    this.textOverflow((undefined as TextOverflowOptions | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.fontFamily((modifier._Text_fontFamily_0_0value as string | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.maxLines((modifier._Text_maxLines_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.decoration((modifier._Text_decoration_0_0value as DecorationStyleInterface | undefined));
                    break;
                }
                default: {
                    this.decoration((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.letterSpacing((modifier._Text_letterSpacing_0_0value as double | string | undefined));
                    break;
                }
                default: {
                    this.letterSpacing((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.textCase((modifier._Text_textCase_0_0value as TextCase | undefined));
                    break;
                }
                default: {
                    this.textCase((undefined as TextCase | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.baselineOffset((modifier._Text_baselineOffset_0_0value as double | string | undefined));
                    break;
                }
                default: {
                    this.baselineOffset((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.copyOption((modifier._Text_copyOption_0_0value as CopyOptions | undefined));
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.draggable((modifier._Text_draggable_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.textShadow((modifier._Text_textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    break;
                }
                default: {
                    this.textShadow((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.heightAdaptivePolicy((modifier._Text_heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.textIndent((modifier._Text_textIndent_0_0value as Length | undefined));
                    break;
                }
                default: {
                    this.textIndent((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.wordBreak((modifier._Text_wordBreak_0_0value as WordBreak | undefined));
                    break;
                }
                default: {
                    this.wordBreak((undefined as WordBreak | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.lineBreakStrategy((modifier._Text_lineBreakStrategy_0_0value as LineBreakStrategy | undefined));
                    break;
                }
                default: {
                    this.lineBreakStrategy((undefined as LineBreakStrategy | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.onCopy((modifier._Text_onCopy_0_0value as ((breakpoints: string) => void) | undefined));
                    break;
                }
                default: {
                    this.onCopy((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.onWillCopy((modifier._Text_onWillCopy_0_0value as arkui_component_common_Callback<string, boolean> | undefined));
                    break;
                }
                default: {
                    this.onWillCopy((undefined as arkui_component_common_Callback<string, boolean> | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.caretColor((modifier._Text_caretColor_0_0value as ResourceColor | undefined));
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
                    this.selectedBackgroundColor((modifier._Text_selectedBackgroundColor_0_0value as ResourceColor | undefined));
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
                    this.ellipsisMode((modifier._Text_ellipsisMode_0_0value as EllipsisMode | undefined));
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
                    this.enableDataDetector((modifier._Text_enableDataDetector_0_0value as boolean | undefined));
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
                    this.dataDetectorConfig((modifier._Text_dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
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
                    this.onTextSelectionChange((modifier._Text_onTextSelectionChange_0_0value as ((first: int32,last: int32) => void) | undefined));
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
                    this.fontFeature((modifier._Text_fontFeature_0_0value as string | undefined));
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
                    this.marqueeOptions((modifier._Text_marqueeOptions_0_0value as TextMarqueeOptions | undefined));
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
                    this.onMarqueeStateChange((modifier._Text_onMarqueeStateChange_0_0value as arkui_component_common_Callback<MarqueeState, void> | undefined));
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
                    this.privacySensitive((modifier._Text_privacySensitive_0_0value as boolean | undefined));
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
                    this.textSelectable((modifier._Text_textSelectable_0_0value as TextSelectableMode | undefined));
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
                    this.editMenuOptions((modifier._Text_editMenuOptions_0_0value as EditMenuOptions | undefined));
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
                    this.halfLeading((modifier._Text_halfLeading_0_0value as boolean | undefined));
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
                    this.enableHapticFeedback((modifier._Text_enableHapticFeedback_0_0value as boolean | undefined));
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
                    this.includeFontPadding((modifier._Text_includeFontPadding_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.includeFontPadding((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier2(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1:
                case 3: {
                    this.fallbackLineSpacing((modifier._Text_fallbackLineSpacing_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.fallbackLineSpacing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1:
                case 3: {
                    this.optimizeTrailingSpace((modifier._Text_optimizeTrailingSpace_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.optimizeTrailingSpace((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1:
                case 3: {
                    this.shaderStyle((modifier._Text_shaderStyle_0_0value as ShaderStyle | undefined));
                    break;
                }
                default: {
                    this.shaderStyle((undefined as ShaderStyle | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1:
                case 3: {
                    this.enableAutoSpacing((modifier._Text_enableAutoSpacing_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableAutoSpacing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1:
                case 3: {
                    this.textVerticalAlign((modifier._Text_textVerticalAlign_0_0value as TextVerticalAlign | undefined));
                    break;
                }
                default: {
                    this.textVerticalAlign((undefined as TextVerticalAlign | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1:
                case 3: {
                    this.contentTransition((modifier._Text_contentTransition_0_0value as ContentTransition | undefined));
                    break;
                }
                default: {
                    this.contentTransition((undefined as ContentTransition | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1:
                case 3: {
                    this.textContentAlign((modifier._Text_textContentAlign_0_0value as TextContentAlign | undefined));
                    break;
                }
                default: {
                    this.textContentAlign((undefined as TextContentAlign | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1:
                case 3: {
                    this.minLines((modifier._Text_minLines_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.minLines((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1:
                case 3: {
                    this.minLineHeight((modifier._Text_minLineHeight_0_0value as arkui_component_units_LengthMetrics | undefined));
                    break;
                }
                default: {
                    this.minLineHeight((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1:
                case 3: {
                    this.maxLineHeight((modifier._Text_maxLineHeight_0_0value as arkui_component_units_LengthMetrics | undefined));
                    break;
                }
                default: {
                    this.maxLineHeight((undefined as arkui_component_units_LengthMetrics | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1:
                case 3: {
                    this.lineHeightMultiple((modifier._Text_lineHeightMultiple_0_0value as double | undefined));
                    break;
                }
                default: {
                    this.lineHeightMultiple((undefined as double | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1:
                case 3: {
                    this.enableSelectedDataDetector((modifier._Text_enableSelectedDataDetector_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableSelectedDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1:
                case 3: {
                    this.compressLeadingPunctuation((modifier._Text_compressLeadingPunctuation_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.compressLeadingPunctuation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1:
                case 3: {
                    this.selectedDragPreviewStyle((modifier._Text_selectedDragPreviewStyle_0_0value as SelectedDragPreviewStyle | undefined));
                    break;
                }
                default: {
                    this.selectedDragPreviewStyle((undefined as SelectedDragPreviewStyle | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1:
                case 3: {
                    this.textDirection((modifier._Text_textDirection_0_0value as TextDirection | undefined));
                    break;
                }
                default: {
                    this.textDirection((undefined as TextDirection | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1:
                case 3: {
                    this.orphanCharOptimization((modifier._Text_orphanCharOptimization_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.orphanCharOptimization((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1:
                case 3: {
                    this.font((modifier._Text_font_0_0value as arkui_component_units_Font | undefined), (modifier._Text_font_0_1value as FontSettingOptions | undefined));
                    break;
                }
                default: {
                    this.font((undefined as arkui_component_units_Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1:
                case 3: {
                    this.fontWeight((modifier._Text_fontWeight_0_0value as int32 | FontWeight | ResourceStr | undefined), (modifier._Text_fontWeight_0_1value as FontSettingOptions | undefined));
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | ResourceStr | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1:
                case 3: {
                    this.lineSpacing((modifier._Text_lineSpacing_0_0value as arkui_component_units_LengthMetrics | undefined), (modifier._Text_lineSpacing_0_1value as LineSpacingOptions | undefined));
                    break;
                }
                default: {
                    this.lineSpacing((undefined as arkui_component_units_LengthMetrics | undefined), (undefined as LineSpacingOptions | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1:
                case 3: {
                    this.selection((modifier._Text_selection_0_0value as int32 | undefined), (modifier._Text_selection_0_1value as int32 | undefined));
                    break;
                }
                default: {
                    this.selection((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    mergeModifier3(modifier: TextModifier, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1:
                case 3: {
                    this.bindSelectionMenu((modifier._Text_bindSelectionMenu_0_0value as TextSpanType | undefined), (modifier._Text_bindSelectionMenu_0_1value as CustomBuilder | undefined), (modifier._Text_bindSelectionMenu_0_2value as TextResponseType | undefined), (modifier._Text_bindSelectionMenu_0_3value as SelectionMenuOptions | undefined));
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as TextSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as TextResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._Text_flagArray[0]) == (0)) || (true)) {
            this._Text_flagArray[0] = 1
            this._Text_fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[0] = 3
        }
        return this
    }
    fontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[1]) == (0)) || (true)) {
            this._Text_flagArray[1] = 1
            this._Text_fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[1] = 3
        }
        return this
    }
    minFontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[2]) == (0)) || (true)) {
            this._Text_flagArray[2] = 1
            this._Text_minFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[2] = 3
        }
        return this
    }
    maxFontSize(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[3]) == (0)) || (true)) {
            this._Text_flagArray[3] = 1
            this._Text_maxFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[3] = 3
        }
        return this
    }
    minFontScale(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[4]) == (0)) || (true)) {
            this._Text_flagArray[4] = 1
            this._Text_minFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[4] = 3
        }
        return this
    }
    maxFontScale(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[5]) == (0)) || (true)) {
            this._Text_flagArray[5] = 1
            this._Text_maxFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[5] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._Text_flagArray[6]) == (0)) || (true)) {
            this._Text_flagArray[6] = 1
            this._Text_fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[6] = 3
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._Text_flagArray[7]) == (0)) || (true)) {
            this._Text_flagArray[7] = 1
            this._Text_textAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[7] = 3
        }
        return this
    }
    lineHeight(value: double | string | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[8]) == (0)) || (true)) {
            this._Text_flagArray[8] = 1
            this._Text_lineHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[8] = 3
        }
        return this
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        if (((this._Text_flagArray[9]) == (0)) || (true)) {
            this._Text_flagArray[9] = 1
            this._Text_textOverflow_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[9] = 3
        }
        return this
    }
    fontFamily(value: string | arkui_component_units_Resource | undefined): this {
        if (((this._Text_flagArray[10]) == (0)) || (true)) {
            this._Text_flagArray[10] = 1
            this._Text_fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[10] = 3
        }
        return this
    }
    maxLines(value: int32 | undefined): this {
        if (((this._Text_flagArray[11]) == (0)) || ((this._Text_maxLines_0_0value) !== (value))) {
            this._Text_flagArray[11] = 1
            this._Text_maxLines_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[11] = 3
        }
        return this
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        if (((this._Text_flagArray[12]) == (0)) || (true)) {
            this._Text_flagArray[12] = 1
            this._Text_decoration_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[12] = 3
        }
        return this
    }
    letterSpacing(value: double | string | undefined): this {
        if (((this._Text_flagArray[13]) == (0)) || ((this._Text_letterSpacing_0_0value) !== (value))) {
            this._Text_flagArray[13] = 1
            this._Text_letterSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[13] = 3
        }
        return this
    }
    textCase(value: TextCase | undefined): this {
        if (((this._Text_flagArray[14]) == (0)) || (true)) {
            this._Text_flagArray[14] = 1
            this._Text_textCase_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[14] = 3
        }
        return this
    }
    baselineOffset(value: double | string | undefined): this {
        if (((this._Text_flagArray[15]) == (0)) || ((this._Text_baselineOffset_0_0value) !== (value))) {
            this._Text_flagArray[15] = 1
            this._Text_baselineOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[15] = 3
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._Text_flagArray[16]) == (0)) || (true)) {
            this._Text_flagArray[16] = 1
            this._Text_copyOption_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[16] = 3
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._Text_flagArray[17]) == (0)) || ((this._Text_draggable_0_0value) !== (value))) {
            this._Text_flagArray[17] = 1
            this._Text_draggable_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[17] = 3
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._Text_flagArray[18]) == (0)) || (true)) {
            this._Text_flagArray[18] = 1
            this._Text_textShadow_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[18] = 3
        }
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (((this._Text_flagArray[19]) == (0)) || (true)) {
            this._Text_flagArray[19] = 1
            this._Text_heightAdaptivePolicy_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[19] = 3
        }
        return this
    }
    textIndent(value: Length | undefined): this {
        if (((this._Text_flagArray[20]) == (0)) || (true)) {
            this._Text_flagArray[20] = 1
            this._Text_textIndent_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[20] = 3
        }
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        if (((this._Text_flagArray[21]) == (0)) || (true)) {
            this._Text_flagArray[21] = 1
            this._Text_wordBreak_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[21] = 3
        }
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (((this._Text_flagArray[22]) == (0)) || (true)) {
            this._Text_flagArray[22] = 1
            this._Text_lineBreakStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[22] = 3
        }
        return this
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        if (((this._Text_flagArray[23]) == (0)) || (true)) {
            this._Text_flagArray[23] = 1
            this._Text_onCopy_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[23] = 3
        }
        return this
    }
    onWillCopy(value: arkui_component_common_Callback<string, boolean> | undefined): this {
        if (((this._Text_flagArray[24]) == (0)) || (true)) {
            this._Text_flagArray[24] = 1
            this._Text_onWillCopy_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[24] = 3
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._Text_flagArray[25]) == (0)) || (true)) {
            this._Text_flagArray[25] = 1
            this._Text_caretColor_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[25] = 3
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._Text_flagArray[26]) == (0)) || (true)) {
            this._Text_flagArray[26] = 1
            this._Text_selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[26] = 3
        }
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        if (((this._Text_flagArray[27]) == (0)) || (true)) {
            this._Text_flagArray[27] = 1
            this._Text_ellipsisMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[27] = 3
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._Text_flagArray[28]) == (0)) || ((this._Text_enableDataDetector_0_0value) !== (value))) {
            this._Text_flagArray[28] = 1
            this._Text_enableDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[28] = 3
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._Text_flagArray[29]) == (0)) || (true)) {
            this._Text_flagArray[29] = 1
            this._Text_dataDetectorConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[29] = 3
        }
        return this
    }
    onTextSelectionChange(value: ((first: int32,last: int32) => void) | undefined): this {
        if (((this._Text_flagArray[30]) == (0)) || (true)) {
            this._Text_flagArray[30] = 1
            this._Text_onTextSelectionChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[30] = 3
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._Text_flagArray[31]) == (0)) || ((this._Text_fontFeature_0_0value) !== (value))) {
            this._Text_flagArray[31] = 1
            this._Text_fontFeature_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[31] = 3
        }
        return this
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (((this._Text_flagArray[32]) == (0)) || (true)) {
            this._Text_flagArray[32] = 1
            this._Text_marqueeOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[32] = 3
        }
        return this
    }
    onMarqueeStateChange(value: arkui_component_common_Callback<MarqueeState, void> | undefined): this {
        if (((this._Text_flagArray[33]) == (0)) || (true)) {
            this._Text_flagArray[33] = 1
            this._Text_onMarqueeStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[33] = 3
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._Text_flagArray[34]) == (0)) || ((this._Text_privacySensitive_0_0value) !== (value))) {
            this._Text_flagArray[34] = 1
            this._Text_privacySensitive_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[34] = 3
        }
        return this
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        if (((this._Text_flagArray[35]) == (0)) || (true)) {
            this._Text_flagArray[35] = 1
            this._Text_textSelectable_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[35] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._Text_flagArray[36]) == (0)) || (true)) {
            this._Text_flagArray[36] = 1
            this._Text_editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[36] = 3
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._Text_flagArray[37]) == (0)) || ((this._Text_halfLeading_0_0value) !== (value))) {
            this._Text_flagArray[37] = 1
            this._Text_halfLeading_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[37] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._Text_flagArray[38]) == (0)) || ((this._Text_enableHapticFeedback_0_0value) !== (value))) {
            this._Text_flagArray[38] = 1
            this._Text_enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[38] = 3
        }
        return this
    }
    includeFontPadding(value: boolean | undefined): this {
        if (((this._Text_flagArray[39]) == (0)) || ((this._Text_includeFontPadding_0_0value) !== (value))) {
            this._Text_flagArray[39] = 1
            this._Text_includeFontPadding_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[39] = 3
        }
        return this
    }
    fallbackLineSpacing(value: boolean | undefined): this {
        if (((this._Text_flagArray[40]) == (0)) || ((this._Text_fallbackLineSpacing_0_0value) !== (value))) {
            this._Text_flagArray[40] = 1
            this._Text_fallbackLineSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[40] = 3
        }
        return this
    }
    optimizeTrailingSpace(value: boolean | undefined): this {
        if (((this._Text_flagArray[41]) == (0)) || ((this._Text_optimizeTrailingSpace_0_0value) !== (value))) {
            this._Text_flagArray[41] = 1
            this._Text_optimizeTrailingSpace_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[41] = 3
        }
        return this
    }
    shaderStyle(value: ShaderStyle | undefined): this {
        if (((this._Text_flagArray[42]) == (0)) || (true)) {
            this._Text_flagArray[42] = 1
            this._Text_shaderStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[42] = 3
        }
        return this
    }
    enableAutoSpacing(value: boolean | undefined): this {
        if (((this._Text_flagArray[43]) == (0)) || ((this._Text_enableAutoSpacing_0_0value) !== (value))) {
            this._Text_flagArray[43] = 1
            this._Text_enableAutoSpacing_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[43] = 3
        }
        return this
    }
    textVerticalAlign(value: TextVerticalAlign | undefined): this {
        if (((this._Text_flagArray[44]) == (0)) || (true)) {
            this._Text_flagArray[44] = 1
            this._Text_textVerticalAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[44] = 3
        }
        return this
    }
    contentTransition(value: ContentTransition | undefined): this {
        if (((this._Text_flagArray[45]) == (0)) || (true)) {
            this._Text_flagArray[45] = 1
            this._Text_contentTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[45] = 3
        }
        return this
    }
    textContentAlign(value: TextContentAlign | undefined): this {
        if (((this._Text_flagArray[46]) == (0)) || (true)) {
            this._Text_flagArray[46] = 1
            this._Text_textContentAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[46] = 3
        }
        return this
    }
    minLines(value: int32 | undefined): this {
        if (((this._Text_flagArray[47]) == (0)) || ((this._Text_minLines_0_0value) !== (value))) {
            this._Text_flagArray[47] = 1
            this._Text_minLines_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[47] = 3
        }
        return this
    }
    minLineHeight(value: arkui_component_units_LengthMetrics | undefined): this {
        if (((this._Text_flagArray[48]) == (0)) || (true)) {
            this._Text_flagArray[48] = 1
            this._Text_minLineHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[48] = 3
        }
        return this
    }
    maxLineHeight(value: arkui_component_units_LengthMetrics | undefined): this {
        if (((this._Text_flagArray[49]) == (0)) || (true)) {
            this._Text_flagArray[49] = 1
            this._Text_maxLineHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[49] = 3
        }
        return this
    }
    lineHeightMultiple(value: double | undefined): this {
        if (((this._Text_flagArray[50]) == (0)) || ((this._Text_lineHeightMultiple_0_0value) !== (value))) {
            this._Text_flagArray[50] = 1
            this._Text_lineHeightMultiple_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[50] = 3
        }
        return this
    }
    enableSelectedDataDetector(value: boolean | undefined): this {
        if (((this._Text_flagArray[51]) == (0)) || ((this._Text_enableSelectedDataDetector_0_0value) !== (value))) {
            this._Text_flagArray[51] = 1
            this._Text_enableSelectedDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[51] = 3
        }
        return this
    }
    compressLeadingPunctuation(value: boolean | undefined): this {
        if (((this._Text_flagArray[52]) == (0)) || ((this._Text_compressLeadingPunctuation_0_0value) !== (value))) {
            this._Text_flagArray[52] = 1
            this._Text_compressLeadingPunctuation_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[52] = 3
        }
        return this
    }
    selectedDragPreviewStyle(value: SelectedDragPreviewStyle | undefined): this {
        if (((this._Text_flagArray[53]) == (0)) || (true)) {
            this._Text_flagArray[53] = 1
            this._Text_selectedDragPreviewStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[53] = 3
        }
        return this
    }
    textDirection(value: TextDirection | undefined): this {
        if (((this._Text_flagArray[54]) == (0)) || (true)) {
            this._Text_flagArray[54] = 1
            this._Text_textDirection_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[54] = 3
        }
        return this
    }
    orphanCharOptimization(value: boolean | undefined): this {
        if (((this._Text_flagArray[55]) == (0)) || ((this._Text_orphanCharOptimization_0_0value) !== (value))) {
            this._Text_flagArray[55] = 1
            this._Text_orphanCharOptimization_0_0value = value
            this._state.fireChange()
        } else {
            this._Text_flagArray[55] = 3
        }
        return this
    }
    font(fontValue: arkui_component_units_Font | undefined, options?: FontSettingOptions): this {
        if (((this._Text_flagArray[56]) == (0)) || (true) || (true)) {
            this._Text_flagArray[56] = 1
            this._Text_font_0_0value = fontValue
            this._Text_font_0_1value = options
            this._state.fireChange()
        } else {
            this._Text_flagArray[56] = 3
        }
        return this
    }
    fontWeight(weight: int32 | FontWeight | ResourceStr | undefined, options?: FontSettingOptions): this {
        if (((this._Text_flagArray[57]) == (0)) || (true) || (true)) {
            this._Text_flagArray[57] = 1
            this._Text_fontWeight_0_0value = weight
            this._Text_fontWeight_0_1value = options
            this._state.fireChange()
        } else {
            this._Text_flagArray[57] = 3
        }
        return this
    }
    lineSpacing(value: arkui_component_units_LengthMetrics | undefined, options?: LineSpacingOptions): this {
        if (((this._Text_flagArray[58]) == (0)) || (true) || (true)) {
            this._Text_flagArray[58] = 1
            this._Text_lineSpacing_0_0value = value
            this._Text_lineSpacing_0_1value = options
            this._state.fireChange()
        } else {
            this._Text_flagArray[58] = 3
        }
        return this
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        if (((this._Text_flagArray[59]) == (0)) || ((this._Text_selection_0_0value) !== (selectionStart)) || ((this._Text_selection_0_1value) !== (selectionEnd))) {
            this._Text_flagArray[59] = 1
            this._Text_selection_0_0value = selectionStart
            this._Text_selection_0_1value = selectionEnd
            this._state.fireChange()
        } else {
            this._Text_flagArray[59] = 3
        }
        return this
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._Text_flagArray[60]) == (0)) || (true) || (true) || (true) || (true)) {
            this._Text_flagArray[60] = 1
            this._Text_bindSelectionMenu_0_0value = spanType
            this._Text_bindSelectionMenu_0_1value = content
            this._Text_bindSelectionMenu_0_2value = responseType
            this._Text_bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else {
            this._Text_flagArray[60] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
