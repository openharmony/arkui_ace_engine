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
import { CopyOptions, CustomBuilder, DecorationStyleInterface, EditMenuOptions, EllipsisMode, Font, FontSettingOptions, FontStyle, FontWeight, Length, LineBreakStrategy, MarqueeState, ResourceColor, SelectionMenuOptions, ShadowOptions, TextAlign, TextAttribute, TextCase, TextDataDetectorConfig, TextHeightAdaptivePolicy, TextMarqueeOptions, TextOverflowOptions, TextResponseType, TextSelectableMode, TextSpanType, WordBreak } from "../../component";
import { ArkCommonMethodPeer } from "../../component";
import { ArkTextPeer } from "../../component";
import { LengthMetrics } from "../../Graphics";
import { Resource } from "global.resource"
import { runtimeType, RuntimeType,  } from "@koalaui/interop"
import { TextOptions } from "../../component/text";
export class ArkTextNode extends ArkBaseNode  implements TextAttribute  {
    constructParam(...params: Object[]): this {
        if (params.length > 2) {
            throw new Error('more than 2 parameters')
        }
        let content_casted : string | Resource | undefined = undefined
        let value_casted : TextOptions | undefined = undefined
        if (params.length >= 1) {
            if (typeof(params[0]) == "string") {
                content_casted = params[0] as string
            } else if (typeof(params[0]) == "object") {
                content_casted = params[0] as string
            }
        }
        if (params.length == 2) {
            const param1_type = runtimeType(params[1])
            if (RuntimeType.OBJECT == param1_type) {
                value_casted = params[1] as TextOptions
            }
        }
        this.getPeer().setTextOptionsAttribute(content_casted, value_casted)
        return this;
    }
    getPeer() : ArkTextPeer {
        return this.peer as ArkTextPeer
    }
    initialize(content?: string | Resource, value?: TextOptions): this {
        const content_casted = content as (string | Resource | undefined)
        const value_casted = value as (TextOptions | undefined)
        this.getPeer()?.setTextOptionsAttribute(content_casted, value_casted)
        this.markDirty();
        return this;
    }
    allowChildTypes(): string[] {
        return ["Span", "ImageSpan", "SymbolSpan", "ContainerSpan"];
    }
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        const fontValue_type = runtimeType(fontValue)
        const options_type = runtimeType(options)
        if ((RuntimeType.OBJECT == fontValue_type) || (RuntimeType.UNDEFINED == fontValue_type)) {
            const fontValue_casted = fontValue as (Font | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.font1Attribute(fontValue_casted, options_casted)
            this.markDirty();
            return this
        }
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.fontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontSize(value: number | string | Resource | undefined): this {
        const value_casted = value as (number | string | Resource | undefined)
        this.getPeer()?.fontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontSize(value: number | string | Resource | undefined): this {
        const value_casted = value as (number | string | Resource | undefined)
        this.getPeer()?.minFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        const value_casted = value as (number | string | Resource | undefined)
        this.getPeer()?.maxFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.minFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.maxFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        const value_casted = value as (FontStyle | undefined)
        this.getPeer()?.fontStyleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        const weight_type = runtimeType(weight)
        const options_type = runtimeType(options)
        if ((RuntimeType.NUMBER == weight_type) || (RuntimeType.NUMBER == weight_type) || (RuntimeType.STRING == weight_type) || (RuntimeType.UNDEFINED == weight_type)) {
            const weight_casted = weight as (number | FontWeight | string | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.fontWeight1Attribute(weight_casted, options_casted)
            this.markDirty();
            return this
        }
        return this;
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        const value_casted = value as (LengthMetrics | undefined)
        this.getPeer()?.lineSpacingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textAlign(value : TextAlign | undefined) : this {
        const value_casted = value as (TextAlign | undefined)
        this.getPeer()?.textAlignAttribute(value_casted)
        this.markDirty();
        return this;
    }
    lineHeight(value: number | string | Resource | undefined): this {
        const value_casted = value as (TextAlign | undefined)
        this.getPeer()?.textAlignAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        const value_casted = value as (TextOverflowOptions | undefined)
        this.getPeer()?.textOverflowAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontFamily(value: string | Resource | undefined): this {
        const value_casted = value as (string | Resource | undefined)
        this.getPeer()?.fontFamilyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxLines(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.maxLinesAttribute(value_casted)
        this.markDirty();
        return this;
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        const value_casted = value as (DecorationStyleInterface | undefined)
        this.getPeer()?.decorationAttribute(value_casted)
        this.markDirty();
        return this;
    }
    letterSpacing(value: number | string | undefined): this {
        const value_casted = value as (number | string | undefined)
        this.getPeer()?.letterSpacingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textCase(value: TextCase | undefined): this {
        const value_casted = value as (TextCase | undefined)
        this.getPeer()?.textCaseAttribute(value_casted)
        this.markDirty();
        return this;
    }
    baselineOffset(value: number | string | undefined): this {
        const value_casted = value as (number | string | undefined)
        this.getPeer()?.baselineOffsetAttribute(value_casted)
        this.markDirty();
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        const value_casted = value as (CopyOptions | undefined)
        this.getPeer()?.copyOptionAttribute(value_casted)
        this.markDirty();
        return this;
    }
    draggable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.draggableAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
        this.getPeer()?.textShadowAttribute(value_casted)
        this.markDirty();
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        const value_casted = value as (TextHeightAdaptivePolicy | undefined)
        this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textIndent(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.textIndentAttribute(value_casted)
        this.markDirty();
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        const value_casted = value as (WordBreak | undefined)
        this.getPeer()?.wordBreakAttribute(value_casted)
        this.markDirty();
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        const value_casted = value as (LineBreakStrategy | undefined)
        this.getPeer()?.lineBreakStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        const value_casted = value as (((breakpoints: string) => void) | undefined)
        this.getPeer()?.onCopyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.caretColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        const value_casted = value as (EllipsisMode | undefined)
        this.getPeer()?.ellipsisModeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    enableDataDetector(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.enableDataDetectorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        const value_casted = value as (TextDataDetectorConfig | undefined)
        this.getPeer()?.dataDetectorConfigAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this {
        const value_casted = value as (((first: number,last: number) => void) | undefined)
        this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.fontFeatureAttribute(value_casted)
        this.markDirty();
        return this;
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        const value_casted = value as (TextMarqueeOptions | undefined)
        this.getPeer()?.marqueeOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this {
        const value_casted = value as (((parameter: MarqueeState) => void) | undefined)
        this.getPeer()?.onMarqueeStateChangeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    privacySensitive(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.privacySensitiveAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        const value_casted = value as (TextSelectableMode | undefined)
        this.getPeer()?.textSelectableAttribute(value_casted)
        this.markDirty();
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        const value_casted = value as (EditMenuOptions | undefined)
        this.getPeer()?.editMenuOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.halfLeadingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
        this.markDirty();
        return this;
    }
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        const selectionStart_casted = selectionStart as (number | undefined)
        const selectionEnd_casted = selectionEnd as (number | undefined)
        this.getPeer()?.selectionAttribute(selectionStart_casted, selectionEnd_casted)
        this.markDirty();
        return this;
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        const spanType_casted = spanType as (TextSpanType | undefined)
        const content_casted = content as (CustomBuilder | undefined)
        const responseType_casted = responseType as (TextResponseType | undefined)
        const options_casted = options as (SelectionMenuOptions)
        this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
        this.markDirty();
        return this;
    }
}
