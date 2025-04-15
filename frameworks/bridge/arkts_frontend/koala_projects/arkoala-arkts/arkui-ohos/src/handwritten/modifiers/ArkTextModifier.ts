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

import { TextAttribute, TextAlign, CopyOptions, CustomBuilder, DecorationStyleInterface, EditMenuOptions, EllipsisMode,
    Font, FontSettingOptions, FontStyle, LengthMetrics, LineBreakStrategy, SelectionMenuOptions, ShadowOptions,
    TextCase, TextDataDetectorConfig, TextHeightAdaptivePolicy, TextOptions, TextOverflowOptions, TextResponseType,
    TextSelectableMode, TextSpanType, WordBreak } from "../../";
import { ArkTextPeer } from "../../generated/peers/ArkTextPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";
import { Resource } from "global/resource";
import { Length, ResourceColor } from "./../../component/units";
import { FontWeight } from "./../../component/enums";


class TextAlignModifier extends ModifierWithKey<TextAlign> {
    static identity: string = 'textAlign';

    constructor(value: TextAlign) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let textPeerNode = node as ArkTextPeer
        if (reset) {
            // textPeerNode.resetTextAlignAttribute();
        } else {
            textPeerNode.textAlignAttribute(this.value!);
        }
    }

    static factory(value: TextAlign): TextAlignModifier {
        return new TextAlignModifier(value)
    }
}

/** @memo:stable */
export class ArkTextAttributeSet extends ArkCommonAttributeSet implements TextAttribute {
    /** @memo */
    setTextOptions(content?: string | Resource, value?: TextOptions) : this {
        return this;
    }
    /** @memo */
    font(fontValue: Font, options?: FontSettingOptions): this {
        return this;
    }
    /** @memo */
    fontColor(value: ResourceColor): this {
        return this;
    }
    /** @memo */
    fontSize(value: number | string | Resource): this {
        return this;
    }
    /** @memo */
    minFontSize(value: number | string | Resource): this {
        return this;
    }
    /** @memo */
    maxFontSize(value: number | string | Resource): this {
        return this;
    }
    /** @memo */
    minFontScale(value: number | Resource): this {
        return this;
    }
    /** @memo */
    maxFontScale(value: number | Resource): this {
        return this;
    }
    /** @memo */
    fontStyle(value: FontStyle): this {
        return this;
    }
    /** @memo */
    fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this {
        return this;
    }
    /** @memo */
    lineSpacing(value: LengthMetrics): this {
        return this;
    }
    /** @memo */
    textAlign(value: TextAlign | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier.factory, value as TextAlign);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, TextAlignModifier.identity);
        }
        return this;
    }
    /** @memo */
    lineHeight(value: number | string | Resource): this {
        return this;
    }
    /** @memo */
    textOverflow(value: TextOverflowOptions): this {
        return this;
    }
    /** @memo */
    fontFamily(value: string | Resource): this {
        return this;
    }
    /** @memo */
    maxLines(value: number): this {
        return this;
    }
    /** @memo */
    decoration(value: DecorationStyleInterface): this {
        return this;
    }
    /** @memo */
    letterSpacing(value: number | string): this {
        return this;
    }
    /** @memo */
    textCase(value: TextCase): this {
        return this;
    }
    /** @memo */
    baselineOffset(value: number | string): this {
        return this;
    }
    /** @memo */
    copyOption(value: CopyOptions): this {
        return this;
    }
    /** @memo */
    draggable(value: boolean): this {
        return this;
    }
    /** @memo */
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this {
        return this;
    }
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        return this;
    }
    /** @memo */
    textIndent(value: Length): this {
        return this;
    }
    /** @memo */
    wordBreak(value: WordBreak): this {
        return this;
    }
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this {
        return this;
    }
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this {
        return this;
    }
    /** @memo */
    caretColor(value: ResourceColor): this {
        return this;
    }
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this {
        return this;
    }
    /** @memo */
    ellipsisMode(value: EllipsisMode): this {
        return this;
    }
    /** @memo */
    enableDataDetector(value: boolean): this {
        return this;
    }
    /** @memo */
    dataDetectorConfig(value: TextDataDetectorConfig): this {
        return this;
    }
    /** @memo */
    onTextSelectionChange(value: ((first: number,last: number) => void)): this {
        return this;
    }
    /** @memo */
    fontFeature(value: string): this {
        return this;
    }
    /** @memo */
    privacySensitive(value: boolean): this {
        return this;
    }
    /** @memo */
    textSelectable(value: TextSelectableMode): this {
        return this;
    }
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this {
        return this;
    }
    /** @memo */
    halfLeading(value: boolean): this {
        return this;
    }
    /** @memo */
    enableHapticFeedback(value: boolean): this {
        return this;
    }
    /** @memo */
    selection(selectionStart: number, selectionEnd: number): this {
        return this;
    }
    /** @memo */
    bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this {
        return this;
    }
}

export class TextModifier extends ArkTextAttributeSet implements AttributeModifier<TextAttribute> {
    /** @memo */
    applyNormalAttribute(instance: TextAttribute) : void {}
    /** @memo */
    applyPressedAttribute(instance: TextAttribute) : void {}
    /** @memo */
    applyFocusedAttribute(instance: TextAttribute) : void {}
    /** @memo */
    applyDisabledAttribute(instance: TextAttribute) : void {}
    /** @memo */
    applySelectedAttribute(instance: TextAttribute) : void {}
}