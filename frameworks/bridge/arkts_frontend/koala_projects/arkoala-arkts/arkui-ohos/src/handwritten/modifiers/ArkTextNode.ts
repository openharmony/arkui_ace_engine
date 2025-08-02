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
import { Resource } from "global/resource"
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
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        return this;
    }
    fontSize(value: number | string | Resource | undefined): this {
        return this;
    }
    minFontSize(value: number | string | Resource | undefined): this {
        return this;
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        return this;
    }
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        return this;
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        return this;
    }
 
    lineHeight(value: number | string | Resource | undefined): this {
        return this;
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        return this;
    }
    fontFamily(value: string | Resource | undefined): this {
        return this;
    }
    maxLines(value: number | undefined): this {
        return this;
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        return this;
    }
    letterSpacing(value: number | string | undefined): this {
        return this;
    }
    textCase(value: TextCase | undefined): this {
        return this;
    }
    baselineOffset(value: number | string | undefined): this {
        return this;
    }
    copyOption(value: CopyOptions | undefined): this {
        return this;
    }
    draggable(value: boolean | undefined): this {
        return this;
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this;
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this;
    }
    textIndent(value: Length | undefined): this {
        return this;
    }
    wordBreak(value: WordBreak | undefined): this {
        return this;
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        return this;
    }
    onCopy(value: ((breakpoints: string) => void) | undefined): this {
        return this;
    }
    caretColor(value: ResourceColor | undefined): this {
        return this;
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this;
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        return this;
    }
    enableDataDetector(value: boolean | undefined): this {
        return this;
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        return this;
    }
    onTextSelectionChange(value: ((first: number, last: number) => void) | undefined): this {
        return this;
    }
    fontFeature(value: string | undefined): this {
        return this;
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        return this;
    }
    onMarqueeStateChange(value: ((parameter: MarqueeState) => void) | undefined): this {
        return this;
    }
    privacySensitive(value: boolean | undefined): this {
        return this;
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        return this;
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        return this;
    }
    halfLeading(value: boolean | undefined): this {
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this;
    }
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        return this;
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        return this;
    }
    textAlign(value : TextAlign | undefined) : this {
        InteropNativeModule._NativeLog("text textAlign enter")  
        if (value) {
            this.getPeer().textAlignAttribute(value);
        } else {
            // this.getPeer().resetAlignItemsAttribute(value);
        }
        return this;
    }
}