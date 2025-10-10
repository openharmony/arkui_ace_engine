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
import { CopyOptions, CustomBuilder, DecorationStyleInterface, EditMenuOptions, EllipsisMode, Font, FontSettingOptions, FontStyle, FontWeight, Length, LineBreakStrategy, MarqueeState, ResourceColor, SelectionMenuOptions, ShadowOptions, TextAlign, TextAttribute, TextCase, TextDataDetectorConfig, TextHeightAdaptivePolicy, TextMarqueeOptions, TextOverflowOptions, TextResponseType, TextSelectableMode, TextSpanType, WordBreak } from "../framework";
import { ArkCommonMethodPeer } from "../framework";
import { ArkTextPeer } from "../framework";
import { LengthMetrics } from "../Graphics";
import { Resource } from "global.resource"
import { runtimeType, RuntimeType,  } from "@koalaui/interop"
import { TextOptions } from "../component/text";
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
            this.getPeer()?.setFontAttribute(fontValue_casted, options_casted)
            this.markDirty();
            return this
        }
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setFontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontSize(value: double | string | Resource | undefined): this {
        const value_casted = value as (double | string | Resource | undefined)
        this.getPeer()?.setFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontSize(value: double | string | Resource | undefined): this {
        const value_casted = value as (double | string | Resource | undefined)
        this.getPeer()?.setMinFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontSize(value: double | string | Resource | undefined): this {
        const value_casted = value as (double | string | Resource | undefined)
        this.getPeer()?.setMaxFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontScale(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setMinFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontScale(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setMaxFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        const value_casted = value as (FontStyle | undefined)
        this.getPeer()?.setFontStyleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        const weight_type = runtimeType(weight)
        const options_type = runtimeType(options)
        if ((RuntimeType.NUMBER == weight_type) || (RuntimeType.NUMBER == weight_type) || (RuntimeType.STRING == weight_type) || (RuntimeType.UNDEFINED == weight_type)) {
            const weight_casted = weight as (int32 | FontWeight | string | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.setFontWeightAttribute(weight_casted, options_casted)
            this.markDirty();
            return this
        }
        return this;
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        const value_casted = value as (LengthMetrics | undefined)
        this.getPeer()?.setLineSpacingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textAlign(value : TextAlign | undefined) : this {
        const value_casted = value as (TextAlign | undefined)
        this.getPeer()?.setTextAlignAttribute(value_casted)
        this.markDirty();
        return this;
    }
    lineHeight(value: double | string | Resource | undefined): this {
        const value_casted = value as (TextAlign | undefined)
        this.getPeer()?.setTextAlignAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        const value_casted = value as (TextOverflowOptions | undefined)
        this.getPeer()?.setTextOverflowAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontFamily(value: string | Resource | undefined): this {
        const value_casted = value as (string | Resource | undefined)
        this.getPeer()?.setFontFamilyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxLines(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setMaxLinesAttribute(value_casted)
        this.markDirty();
        return this;
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        const value_casted = value as (DecorationStyleInterface | undefined)
        this.getPeer()?.setDecorationAttribute(value_casted)
        this.markDirty();
        return this;
    }
    letterSpacing(value: double | string | undefined): this {
        const value_casted = value as (double | string | undefined)
        this.getPeer()?.setLetterSpacingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textCase(value: TextCase | undefined): this {
        const value_casted = value as (TextCase | undefined)
        this.getPeer()?.setTextCaseAttribute(value_casted)
        this.markDirty();
        return this;
    }
    baselineOffset(value: double | string | undefined): this {
        const value_casted = value as (double | string | undefined)
        this.getPeer()?.setBaselineOffsetAttribute(value_casted)
        this.markDirty();
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        const value_casted = value as (CopyOptions | undefined)
        this.getPeer()?.setCopyOptionAttribute(value_casted)
        this.markDirty();
        return this;
    }
    draggable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setDraggableAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
        this.getPeer()?.setTextShadowAttribute(value_casted)
        this.markDirty();
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        const value_casted = value as (TextHeightAdaptivePolicy | undefined)
        this.getPeer()?.setHeightAdaptivePolicyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textIndent(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setTextIndentAttribute(value_casted)
        this.markDirty();
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        const value_casted = value as (WordBreak | undefined)
        this.getPeer()?.setWordBreakAttribute(value_casted)
        this.markDirty();
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        const value_casted = value as (LineBreakStrategy | undefined)
        this.getPeer()?.setLineBreakStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        const value_casted = value as (((breakpoints: string) => void) | undefined)
        this.getPeer()?.setOnCopyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setCaretColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        const value_casted = value as (EllipsisMode | undefined)
        this.getPeer()?.setEllipsisModeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    enableDataDetector(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableDataDetectorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        const value_casted = value as (TextDataDetectorConfig | undefined)
        this.getPeer()?.setDataDetectorConfigAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onTextSelectionChange(value: ((first: int32, last: int32) => void) | undefined): this {
        const value_casted = value as (((first: int32,last: int32) => void) | undefined)
        this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontFeature(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setFontFeatureAttribute(value_casted)
        this.markDirty();
        return this;
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        const value_casted = value as (TextMarqueeOptions | undefined)
        this.getPeer()?.setMarqueeOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this {
        const value_casted = value as (((parameter: MarqueeState) => void) | undefined)
        this.getPeer()?.setOnMarqueeStateChangeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    privacySensitive(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
        this.markDirty();
        return this;
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        const value_casted = value as (TextSelectableMode | undefined)
        this.getPeer()?.setTextSelectableAttribute(value_casted)
        this.markDirty();
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        const value_casted = value as (EditMenuOptions | undefined)
        this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setHalfLeadingAttribute(value_casted)
        this.markDirty();
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
        this.markDirty();
        return this;
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        const selectionStart_casted = selectionStart as (int32 | undefined)
        const selectionEnd_casted = selectionEnd as (int32 | undefined)
        this.getPeer()?.setSelectionAttribute(selectionStart_casted, selectionEnd_casted)
        this.markDirty();
        return this;
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        const spanType_casted = spanType as (TextSpanType | undefined)
        const content_casted = content as (CustomBuilder | undefined)
        const responseType_casted = responseType as (TextResponseType | undefined)
        const options_casted = options as (SelectionMenuOptions)
        this.getPeer()?.setBindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
        this.markDirty();
        return this;
    }
}
