// /*
//  * Copyright (c) 2025 Huawei Device Co., Ltd.
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * you may not use this file except in compliance with the License.
//  * You may obtain a copy of the License at
//  *
//  * http://www.apache.org/licenses/LICENSE-2.0
//  *
//  * Unless required by applicable law or agreed to in writing, software
//  * distributed under the License is distributed on an "AS IS" BASIS,
//  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  * See the License for the specific language governing permissions and
//  * limitations under the License.
//  */

import { int32 } from "@koalaui/common"


import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";
import { AttributeModifier, CopyOptions, CustomBuilder, DecorationStyleInterface, EditMenuOptions, EllipsisMode, Font, FontSettingOptions, FontStyle, FontWeight, Length, LineBreakStrategy, MarqueeState, ResourceColor, SelectionMenuOptions, ShadowOptions, TextAlign, TextAttribute, TextCase, TextDataDetectorConfig, TextHeightAdaptivePolicy, TextMarqueeOptions, TextOverflowOptions, TextResponseType, TextSelectableMode, TextSpanType, WordBreak } from "../../component";
import { ArkCommonMethodPeer } from "../../component";
import { ArkTextPeer } from "../../component";
import { LengthMetrics } from "../../Graphics";
import { Resource } from "global/resource"
class TextAlignModifier extends ModifierWithKey<int32> {
    static identity: string = 'textAlign';

    constructor(value: int32) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let textPeerNode = node as ArkTextPeer
        if (reset) {
            // textPeerNode.resetTextAlignAttribute();
        } else {
            if (this.value! === 1) {
                textPeerNode.textAlignAttribute(TextAlign.Start);
            } else if (this.value! === 0) {
                textPeerNode.textAlignAttribute(TextAlign.Center);
            } else if (this.value! === 2) {
                textPeerNode.textAlignAttribute(TextAlign.End);
            } else {
                textPeerNode.textAlignAttribute(TextAlign.JUSTIFY);
            }
        }
    }

    static factory(value: int32): TextAlignModifier {
        return new TextAlignModifier(value)
    }
}

export class ArkTextAttributeSet extends ArkCommonAttributeSet implements TextAttribute {
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
    textAlign(value: TextAlign | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier.factory, value as TextAlign as int32);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, TextAlignModifier.identity);
        }
        return this;
    }

}
export class TextModifier extends ArkTextAttributeSet implements AttributeModifier<TextAttribute> {
    attributeSet: ArkTextAttributeSet = new ArkTextAttributeSet();
    applyNormalAttribute(instance: TextAttribute) : void {}
    applyPressedAttribute(instance: TextAttribute) : void {}
    applyFocusedAttribute(instance: TextAttribute) : void {}
    applyDisabledAttribute(instance: TextAttribute) : void {}
    applySelectedAttribute(instance: TextAttribute) : void {}
}

