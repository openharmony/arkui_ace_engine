/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { memo_stable } from '@koalaui.runtime.annotations';
import {
    ArkCommonMethodPeer,
    CommonMethod,
    ArkCommonMethodStyle,
    ArkCommonMethodComponent,
} from 'arkui/component/common';
import { ShadowOptions, AttributeModifier } from 'arkui.component.common';
import { CustomBuilder } from 'arkui.component.builder';
import { ComponentBase } from 'arkui.ComponentBase';
import { ResourceColor, Length, Font } from 'arkui.component.units';
import {
    MarqueeState,
    TextOverflowOptions,
    TextMarqueeOptions,
    TextSpanType,
    TextResponseType,
    TextOptions,
} from 'arkui.component.text';
import { Resource } from 'global.resource';
import {
    CopyOptions,
    EllipsisMode,
    FontStyle,
    FontWeight,
    LineBreakStrategy,
    TextAlign,
    TextHeightAdaptivePolicy,
    WordBreak,
    TextCase,
    TextSelectableMode,
} from 'arkui.component.enums';
import { TextDataDetectorConfig, EditMenuOptions, FontSettingOptions } from 'arkui.component.textCommon';
import { LengthMetrics } from 'arkui.Graphics';
import { SelectionMenuOptions } from 'arkui.component.richEditor';
import { DecorationStyleInterface } from 'arkui.component.styledString';

type KPointer = long
type int32 = int

export declare class ArkTextPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string);
    constructor(peerPtr: KPointer, id: int32);
    protected constructor(peerPtr: KPointer, id: int32, name: string, flags: int32);
    public static create(component: ComponentBase | undefined, flags?: int32): ArkTextPeer;
    public setTextOptionsAttribute(content?: string | Resource, value?: TextOptions): void;
    public font0Attribute(value: Font | undefined): void;
    public font1Attribute(fontValue: Font | undefined, options?: FontSettingOptions): void;
    public fontColorAttribute(value: ResourceColor | undefined): void;
    public fontSizeAttribute(value: number | string | Resource | undefined): void;
    public minFontSizeAttribute(value: number | string | Resource | undefined): void;
    public maxFontSizeAttribute(value: number | string | Resource | undefined): void;
    public minFontScaleAttribute(value: number | Resource | undefined): void;
    public maxFontScaleAttribute(value: number | Resource | undefined): void;
    public fontStyleAttribute(value: FontStyle | undefined): void;
    public fontWeight0Attribute(value: number | FontWeight | string | undefined): void;
    public fontWeight1Attribute(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): void;
    public lineSpacingAttribute(value: LengthMetrics | undefined): void;
    public textAlignAttribute(value: TextAlign | undefined): void;
    public lineHeightAttribute(value: number | string | Resource | undefined): void;
    public textOverflowAttribute(value: TextOverflowOptions | undefined): void;
    public fontFamilyAttribute(value: string | Resource | undefined): void;
    public maxLinesAttribute(value: number | undefined): void;
    public decorationAttribute(value: DecorationStyleInterface | undefined): void;
    public letterSpacingAttribute(value: number | string | undefined): void;
    public textCaseAttribute(value: TextCase | undefined): void;
    public baselineOffsetAttribute(value: number | string | undefined): void;
    public copyOptionAttribute(value: CopyOptions | undefined): void;
    public draggableAttribute(value: boolean | undefined): void;
    public textShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void;
    public heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void;
    public textIndentAttribute(value: Length | undefined): void;
    public wordBreakAttribute(value: WordBreak | undefined): void;
    public lineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void;
    public onCopyAttribute(value: ((breakpoints: string) => void) | undefined): void;
    public caretColorAttribute(value: ResourceColor | undefined): void;
    public selectedBackgroundColorAttribute(value: ResourceColor | undefined): void;
    public ellipsisModeAttribute(value: EllipsisMode | undefined): void;
    public enableDataDetectorAttribute(value: boolean | undefined): void;
    public dataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void;
    public onTextSelectionChangeAttribute(value: ((first: number, last: number) => void) | undefined): void;
    public fontFeatureAttribute(value: string | undefined): void;
    public marqueeOptionsAttribute(value: TextMarqueeOptions | undefined): void;
    public onMarqueeStateChangeAttribute(value: ((parameter: MarqueeState) => void) | undefined): void;
    public privacySensitiveAttribute(value: boolean | undefined): void;
    public textSelectableAttribute(value: TextSelectableMode | undefined): void;
    public editMenuOptionsAttribute(value: EditMenuOptions | undefined): void;
    public halfLeadingAttribute(value: boolean | undefined): void;
    public enableHapticFeedbackAttribute(value: boolean | undefined): void;
    public selectionAttribute(selectionStart: number | undefined, selectionEnd: number | undefined): void;
    public bindSelectionMenuAttribute(
        spanType: TextSpanType | undefined,
        content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined,
        options?: SelectionMenuOptions
    ): void;
}

export interface TextAttribute extends CommonMethod {
    font(fontValue: Font | undefined, options?: FontSettingOptions): this;
    fontColor(value: ResourceColor | undefined): this;
    fontSize(value: number | string | Resource | undefined): this;
    minFontSize(value: number | string | Resource | undefined): this;
    maxFontSize(value: number | string | Resource | undefined): this;
    minFontScale(value: number | Resource | undefined): this;
    maxFontScale(value: number | Resource | undefined): this;
    fontStyle(value: FontStyle | undefined): this;
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this;
    lineSpacing(value: LengthMetrics | undefined): this;
    textAlign(value: TextAlign | undefined): this;
    lineHeight(value: number | string | Resource | undefined): this;
    textOverflow(value: TextOverflowOptions | undefined): this;
    fontFamily(value: string | Resource | undefined): this;
    maxLines(value: number | undefined): this;
    decoration(value: DecorationStyleInterface | undefined): this;
    letterSpacing(value: number | string | undefined): this;
    textCase(value: TextCase | undefined): this;
    baselineOffset(value: number | string | undefined): this;
    copyOption(value: CopyOptions | undefined): this;
    draggable(value: boolean | undefined): this;
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this;
    textIndent(value: Length | undefined): this;
    wordBreak(value: WordBreak | undefined): this;
    lineBreakStrategy(value: LineBreakStrategy | undefined): this;
    onCopy(value: ((breakpoints: string) => void) | undefined): this;
    caretColor(value: ResourceColor | undefined): this;
    selectedBackgroundColor(value: ResourceColor | undefined): this;
    ellipsisMode(value: EllipsisMode | undefined): this;
    enableDataDetector(value: boolean | undefined): this;
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this;
    onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this;
    fontFeature(value: string | undefined): this;
    marqueeOptions(value: TextMarqueeOptions | undefined): this;
    onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this;
    privacySensitive(value: boolean | undefined): this;
    textSelectable(value: TextSelectableMode | undefined): this;
    editMenuOptions(value: EditMenuOptions | undefined): this;
    halfLeading(value: boolean | undefined): this;
    enableHapticFeedback(value: boolean | undefined): this;
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this;
    bindSelectionMenu(
        spanType: TextSpanType | undefined,
        content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined,
        options?: SelectionMenuOptions
    ): this;
}
export declare class ArkTextStyle extends ArkCommonMethodStyle implements TextAttribute {
    public font_value?: Font | undefined;
    public fontColor_value?: ResourceColor | undefined;
    public fontSize_value?: number | string | Resource | undefined;
    public minFontSize_value?: number | string | Resource | undefined;
    public maxFontSize_value?: number | string | Resource | undefined;
    public minFontScale_value?: number | Resource | undefined;
    public maxFontScale_value?: number | Resource | undefined;
    public fontStyle_value?: FontStyle | undefined;
    public fontWeight_value?: number | FontWeight | string | undefined;
    public lineSpacing_value?: LengthMetrics | undefined;
    public textAlign_value?: TextAlign | undefined;
    public lineHeight_value?: number | string | Resource | undefined;
    public textOverflow_value?: TextOverflowOptions | undefined;
    public fontFamily_value?: string | Resource | undefined;
    public maxLines_value?: number | undefined;
    public decoration_value?: DecorationStyleInterface | undefined;
    public letterSpacing_value?: number | string | undefined;
    public textCase_value?: TextCase | undefined;
    public baselineOffset_value?: number | string | undefined;
    public copyOption_value?: CopyOptions | undefined;
    public draggable_value?: boolean | undefined;
    public textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined;
    public heightAdaptivePolicy_value?: TextHeightAdaptivePolicy | undefined;
    public textIndent_value?: Length | undefined;
    public wordBreak_value?: WordBreak | undefined;
    public lineBreakStrategy_value?: LineBreakStrategy | undefined;
    public onCopy_value?: ((breakpoints: string) => void) | undefined;
    public caretColor_value?: ResourceColor | undefined;
    public selectedBackgroundColor_value?: ResourceColor | undefined;
    public ellipsisMode_value?: EllipsisMode | undefined;
    public enableDataDetector_value?: boolean | undefined;
    public dataDetectorConfig_value?: TextDataDetectorConfig | undefined;
    public onTextSelectionChange_value?: ((first: number, last: number) => void) | undefined;
    public fontFeature_value?: string | undefined;
    public marqueeOptions_value?: TextMarqueeOptions | undefined;
    public onMarqueeStateChange_value?: ((parameter: MarqueeState) => void) | undefined;
    public privacySensitive_value?: boolean | undefined;
    public textSelectable_value?: TextSelectableMode | undefined;
    public editMenuOptions_value?: EditMenuOptions | undefined;
    public halfLeading_value?: boolean | undefined;
    public enableHapticFeedback_value?: boolean | undefined;
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this;
    public fontColor(value: ResourceColor | undefined): this;
    public fontSize(value: number | string | Resource | undefined): this;
    public minFontSize(value: number | string | Resource | undefined): this;
    public maxFontSize(value: number | string | Resource | undefined): this;
    public minFontScale(value: number | Resource | undefined): this;
    public maxFontScale(value: number | Resource | undefined): this;
    public fontStyle(value: FontStyle | undefined): this;
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this;
    public lineSpacing(value: LengthMetrics | undefined): this;
    public textAlign(value: TextAlign | undefined): this;
    public lineHeight(value: number | string | Resource | undefined): this;
    public textOverflow(value: TextOverflowOptions | undefined): this;
    public fontFamily(value: string | Resource | undefined): this;
    public maxLines(value: number | undefined): this;
    public decoration(value: DecorationStyleInterface | undefined): this;
    public letterSpacing(value: number | string | undefined): this;
    public textCase(value: TextCase | undefined): this;
    public baselineOffset(value: number | string | undefined): this;
    public copyOption(value: CopyOptions | undefined): this;
    public draggable(value: boolean | undefined): this;
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this;
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this;
    public textIndent(value: Length | undefined): this;
    public wordBreak(value: WordBreak | undefined): this;
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this;
    public onCopy(value: ((breakpoints: string) => void) | undefined): this;
    public caretColor(value: ResourceColor | undefined): this;
    public selectedBackgroundColor(value: ResourceColor | undefined): this;
    public ellipsisMode(value: EllipsisMode | undefined): this;
    public enableDataDetector(value: boolean | undefined): this;
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this;
    public onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this;
    public fontFeature(value: string | undefined): this;
    public marqueeOptions(value: TextMarqueeOptions | undefined): this;
    public onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this;
    public privacySensitive(value: boolean | undefined): this;
    public textSelectable(value: TextSelectableMode | undefined): this;
    public editMenuOptions(value: EditMenuOptions | undefined): this;
    public halfLeading(value: boolean | undefined): this;
    public enableHapticFeedback(value: boolean | undefined): this;
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this;
    public bindSelectionMenu(
        spanType: TextSpanType | undefined,
        content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined,
        options?: SelectionMenuOptions
    ): this;
}

@memo_stable() export declare class ArkTextComponent extends ArkCommonMethodComponent implements TextAttribute {
    public initAttributeSet<T>(modifier: AttributeModifier<T>): void;
    public getPeer(): ArkTextPeer;
    public setTextOptions(content?: string | Resource, value?: TextOptions): this;
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this;
    public fontColor(value: ResourceColor | undefined): this;
    public fontSize(value: number | string | Resource | undefined): this;
    public minFontSize(value: number | string | Resource | undefined): this;
    public maxFontSize(value: number | string | Resource | undefined): this;
    public minFontScale(value: number | Resource | undefined): this;
    public maxFontScale(value: number | Resource | undefined): this;
    public fontStyle(value: FontStyle | undefined): this;
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this;
    public lineSpacing(value: LengthMetrics | undefined): this;
    public textAlign(value: TextAlign | undefined): this;
    public lineHeight(value: number | string | Resource | undefined): this;
    public textOverflow(value: TextOverflowOptions | undefined): this;
    public fontFamily(value: string | Resource | undefined): this;
    public maxLines(value: number | undefined): this;
    public decoration(value: DecorationStyleInterface | undefined): this;
    public letterSpacing(value: number | string | undefined): this;
    public textCase(value: TextCase | undefined): this;
    public baselineOffset(value: number | string | undefined): this;
    public copyOption(value: CopyOptions | undefined): this;
    public draggable(value: boolean | undefined): this;
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this;
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this;
    public textIndent(value: Length | undefined): this;
    public wordBreak(value: WordBreak | undefined): this;
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this;
    public onCopy(value: ((breakpoints: string) => void) | undefined): this;
    public caretColor(value: ResourceColor | undefined): this;
    public selectedBackgroundColor(value: ResourceColor | undefined): this;
    public ellipsisMode(value: EllipsisMode | undefined): this;
    public enableDataDetector(value: boolean | undefined): this;
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this;
    public onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this;
    public fontFeature(value: string | undefined): this;
    public marqueeOptions(value: TextMarqueeOptions | undefined): this;
    public onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this;
    public privacySensitive(value: boolean | undefined): this;
    public textSelectable(value: TextSelectableMode | undefined): this;
    public editMenuOptions(value: EditMenuOptions | undefined): this;
    public halfLeading(value: boolean | undefined): this;
    public enableHapticFeedback(value: boolean | undefined): this;
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this;
    public bindSelectionMenu(
        spanType: TextSpanType | undefined,
        content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined,
        options?: SelectionMenuOptions
    ): this;
    public applyAttributesFinish(): void;
}
