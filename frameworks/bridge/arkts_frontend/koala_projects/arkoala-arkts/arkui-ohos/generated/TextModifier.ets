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
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkTextPeer, TextOverflowOptions, TextMarqueeOptions, MarqueeState, TextAttribute, TextSpanType, TextResponseType } from "./component/text"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CommonMethod, ShadowOptions } from "./component/common"
import { ResourceColor, Length, Font } from "./component/units"
import { Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight } from "./component/enums"
import { Resource } from "global.resource"
import { LengthMetrics } from "arkui.Graphics"
import { DecorationStyleInterface } from "./component/styledString"
import { TextDataDetectorConfig, EditMenuOptions, TextDirection, FontSettingOptions, SelectedDragPreviewStyle } from "./component/textCommon"
import { CustomBuilder } from "./component/builder"
import { SelectionMenuOptions } from "./component/richEditor"
import { TextModifier } from "arkui.TextModifier"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./CallbackTransformer"
export class TextModifier extends CommonMethodModifier implements TextAttribute,AttributeModifier<TextAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextAttribute): void { }
    applyPressedAttribute(instance: TextAttribute): void { }
    applyFocusedAttribute(instance: TextAttribute): void { }
    applyDisabledAttribute(instance: TextAttribute): void { }
    applySelectedAttribute(instance: TextAttribute): void { }
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: double | string | Resource | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: double | string | Resource | undefined
    _maxFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize_0_0value?: double | string | Resource | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: double | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: double | Resource | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _lineSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineSpacing_0_0value?: LengthMetrics | undefined
    _textAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAlign_0_0value?: TextAlign | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: double | string | Resource | undefined
    _textOverflow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textOverflow_0_0value?: TextOverflowOptions | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _maxLines_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLines_0_0value?: int32 | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: DecorationStyleInterface | undefined
    _letterSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing_0_0value?: double | string | undefined
    _textCase_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textCase_0_0value?: TextCase | undefined
    _baselineOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _baselineOffset_0_0value?: double | string | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _draggable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _draggable_0_0value?: boolean | undefined
    _textShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    _heightAdaptivePolicy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    _textIndent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIndent_0_0value?: Length | undefined
    _wordBreak_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _wordBreak_0_0value?: WordBreak | undefined
    _lineBreakStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineBreakStrategy_0_0value?: LineBreakStrategy | undefined
    _onCopy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy_0_0value?: ((value: string) => void) | undefined
    _caretColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretColor_0_0value?: ResourceColor | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _ellipsisMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ellipsisMode_0_0value?: EllipsisMode | undefined
    _enableDataDetector_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDataDetector_0_0value?: boolean | undefined
    _dataDetectorConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    _onTextSelectionChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTextSelectionChange_0_0value?: ((selectionStart: int32,selectionEnd: int32) => void) | undefined
    _fontFeature_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFeature_0_0value?: string | undefined
    _marqueeOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _marqueeOptions_0_0value?: TextMarqueeOptions | undefined
    _onMarqueeStateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onMarqueeStateChange_0_0value?: ((value0: MarqueeState) => void) | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    _textSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textSelectable_0_0value?: TextSelectableMode | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _halfLeading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _halfLeading_0_0value?: boolean | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
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
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _font_0_1value?: FontSettingOptions | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _fontWeight_0_1value?: FontSettingOptions | undefined
    _selection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selection_0_0value?: int32 | undefined
    _selection_0_1value?: int32 | undefined
    _bindSelectionMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSelectionMenu_0_0value?: TextSpanType | undefined
    _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    _bindSelectionMenu_0_2value?: TextResponseType | undefined
    _bindSelectionMenu_0_3value?: SelectionMenuOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTextPeer;
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
                    peer.setFontSizeAttribute((this._fontSize_0_0value as double | string | Resource | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as double | string | Resource | undefined));
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
        if (this._textOverflow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textOverflow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextOverflowAttribute((this._textOverflow_0_0value as TextOverflowOptions | undefined));
                    this._textOverflow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textOverflow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textOverflow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextOverflowAttribute((undefined as TextOverflowOptions | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFamilyAttribute((undefined as string | Resource | undefined));
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
        if (this._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDecorationAttribute((this._decoration_0_0value as DecorationStyleInterface | undefined));
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDecorationAttribute((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (this._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLetterSpacingAttribute((this._letterSpacing_0_0value as double | string | undefined));
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLetterSpacingAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._textCase_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textCase_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextCaseAttribute((this._textCase_0_0value as TextCase | undefined));
                    this._textCase_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textCase_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textCase_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextCaseAttribute((undefined as TextCase | undefined));
                }
            }
        }
        if (this._baselineOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._baselineOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBaselineOffsetAttribute((this._baselineOffset_0_0value as double | string | undefined));
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBaselineOffsetAttribute((undefined as double | string | undefined));
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
        if (this._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._draggable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._textShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextShadowAttribute((this._textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    this._textShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textShadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextShadowAttribute((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
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
        if (this._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextIndentAttribute((this._textIndent_0_0value as Length | undefined));
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextIndentAttribute((undefined as Length | undefined));
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
        if (this._enableDataDetector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDataDetector_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableDataDetectorAttribute((this._enableDataDetector_0_0value as boolean | undefined));
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._dataDetectorConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dataDetectorConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDataDetectorConfigAttribute((this._dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDataDetectorConfigAttribute((undefined as TextDataDetectorConfig | undefined));
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
        if (this._marqueeOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._marqueeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarqueeOptionsAttribute((this._marqueeOptions_0_0value as TextMarqueeOptions | undefined));
                    this._marqueeOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._marqueeOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._marqueeOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarqueeOptionsAttribute((undefined as TextMarqueeOptions | undefined));
                }
            }
        }
        if (this._onMarqueeStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onMarqueeStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnMarqueeStateChangeAttribute((this._onMarqueeStateChange_0_0value as ((value0: MarqueeState) => void) | undefined));
                    this._onMarqueeStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onMarqueeStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onMarqueeStateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnMarqueeStateChangeAttribute((undefined as ((value0: MarqueeState) => void) | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._textSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextSelectableAttribute((this._textSelectable_0_0value as TextSelectableMode | undefined));
                    this._textSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textSelectable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextSelectableAttribute((undefined as TextSelectableMode | undefined));
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
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined), (this._font_0_1value as FontSettingOptions | undefined | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined), (this._fontWeight_0_1value as FontSettingOptions | undefined | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (this._selection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectionAttribute((this._selection_0_0value as int32 | undefined), (this._selection_0_1value as int32 | undefined));
                    this._selection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectionAttribute((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
        if (this._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as TextSpanType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as TextResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptions | undefined | undefined));
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindSelectionMenuAttribute((undefined as TextSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as TextResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
                    this.fontSize((undefined as double | string | Resource | undefined));
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
        if (modifier._textOverflow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textOverflow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textOverflow(modifier._textOverflow_0_0value);
                    break;
                }
                default: {
                    this.textOverflow((undefined as TextOverflowOptions | undefined));
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
                    this.fontFamily((undefined as string | Resource | undefined));
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
        if (modifier._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.decoration(modifier._decoration_0_0value);
                    break;
                }
                default: {
                    this.decoration((undefined as DecorationStyleInterface | undefined));
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
                    this.letterSpacing((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._textCase_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textCase_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textCase(modifier._textCase_0_0value);
                    break;
                }
                default: {
                    this.textCase((undefined as TextCase | undefined));
                }
            }
        }
        if (modifier._baselineOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._baselineOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.baselineOffset(modifier._baselineOffset_0_0value);
                    break;
                }
                default: {
                    this.baselineOffset((undefined as double | string | undefined));
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
        if (modifier._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._textShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textShadow(modifier._textShadow_0_0value);
                    break;
                }
                default: {
                    this.textShadow((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
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
        if (modifier._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textIndent(modifier._textIndent_0_0value);
                    break;
                }
                default: {
                    this.textIndent((undefined as Length | undefined));
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
        if (modifier._enableDataDetector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDataDetector_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDataDetector(modifier._enableDataDetector_0_0value);
                    break;
                }
                default: {
                    this.enableDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._dataDetectorConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dataDetectorConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dataDetectorConfig(modifier._dataDetectorConfig_0_0value);
                    break;
                }
                default: {
                    this.dataDetectorConfig((undefined as TextDataDetectorConfig | undefined));
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
        if (modifier._marqueeOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._marqueeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.marqueeOptions(modifier._marqueeOptions_0_0value);
                    break;
                }
                default: {
                    this.marqueeOptions((undefined as TextMarqueeOptions | undefined));
                }
            }
        }
        if (modifier._onMarqueeStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onMarqueeStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onMarqueeStateChange(modifier._onMarqueeStateChange_0_0value);
                    break;
                }
                default: {
                    this.onMarqueeStateChange((undefined as ((value0: MarqueeState) => void) | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._textSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textSelectable(modifier._textSelectable_0_0value);
                    break;
                }
                default: {
                    this.textSelectable((undefined as TextSelectableMode | undefined));
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
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value, modifier._font_0_1value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value, modifier._fontWeight_0_1value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined), (undefined as FontSettingOptions | undefined | undefined));
                }
            }
        }
        if (modifier._selection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selection(modifier._selection_0_0value, modifier._selection_0_1value);
                    break;
                }
                default: {
                    this.selection((undefined as int32 | undefined), (undefined as int32 | undefined));
                }
            }
        }
        if (modifier._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
    fontSize(value: double | string | Resource | undefined): this {
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
    textOverflow(value: TextOverflowOptions | undefined): this {
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
    fontFamily(value: string | Resource | undefined): this {
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
    decoration(value: DecorationStyleInterface | undefined): this {
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
    letterSpacing(value: double | string | undefined): this {
        if (((this._letterSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._letterSpacing_0_0value) !== (value)))
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
    textCase(value: TextCase | undefined): this {
        if (((this._textCase_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textCase_0_flag = AttributeUpdaterFlag.UPDATE
            this._textCase_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textCase_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    baselineOffset(value: double | string | undefined): this {
        if (((this._baselineOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._baselineOffset_0_0value) !== (value)))
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._baselineOffset_0_0value = value
            this._state.fireChange()
        } else
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.SKIP
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
    draggable(value: boolean | undefined): this {
        if (((this._draggable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable_0_0value) !== (value)))
        {
            this._draggable_0_flag = AttributeUpdaterFlag.UPDATE
            this._draggable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._draggable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._textShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._textShadow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.SKIP
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
    textIndent(value: Length | undefined): this {
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
    enableDataDetector(value: boolean | undefined): this {
        if (((this._enableDataDetector_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDataDetector_0_0value) !== (value)))
        {
            this._enableDataDetector_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableDataDetector_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableDataDetector_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._dataDetectorConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._dataDetectorConfig_0_0value = value
            this._state.fireChange()
        } else
        {
            this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.SKIP
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
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (((this._marqueeOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._marqueeOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._marqueeOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._marqueeOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        if (((this._onMarqueeStateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onMarqueeStateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onMarqueeStateChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onMarqueeStateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        if (((this._textSelectable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textSelectable_0_flag = AttributeUpdaterFlag.UPDATE
            this._textSelectable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textSelectable_0_flag = AttributeUpdaterFlag.SKIP
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
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = fontValue
            this._font_0_1value = options
            this._state.fireChange()
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = weight
            this._fontWeight_0_1value = options
            this._state.fireChange()
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        if (((this._selection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selection_0_0value) !== (selectionStart)) || ((this._selection_0_1value) !== (selectionEnd)))
        {
            this._selection_0_flag = AttributeUpdaterFlag.UPDATE
            this._selection_0_0value = selectionStart
            this._selection_0_1value = selectionEnd
            this._state.fireChange()
        } else
        {
            this._selection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._bindSelectionMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true) || (true))
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindSelectionMenu_0_0value = spanType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextModifier_serializer {
    public static write(buffer: SerializerBase, value: TextModifier): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toTextModifierPtr(value))
    }
    public static read(buffer: DeserializerBase): TextModifier {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromTextModifierPtr(ptr)
    }
}
