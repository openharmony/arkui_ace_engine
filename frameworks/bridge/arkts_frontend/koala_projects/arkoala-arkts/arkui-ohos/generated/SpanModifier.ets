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

import { CommonMethod, ShadowOptions } from "./component/common"
import { TextBackgroundStyle, BaseSpan, ArkSpanPeer, SpanAttribute } from "./component/span"
import { extractors, AttributeModifier } from "#handwritten"
import { LengthMetrics } from "arkui.Graphics"
import { BaseSpanModifier } from "./BaseSpanModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { int32 } from "@koalaui/common"
import { Font, ResourceColor, Length } from "./component/units"
import { Color, FontStyle, FontWeight, TextCase } from "./component/enums"
import { Resource } from "global.resource"
import { DecorationStyleInterface } from "./component/styledString"
export class SpanModifier extends CommonMethodModifier implements SpanAttribute,AttributeModifier<SpanAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SpanAttribute): void { }
    applyPressedAttribute(instance: SpanAttribute): void { }
    applyFocusedAttribute(instance: SpanAttribute): void { }
    applyDisabledAttribute(instance: SpanAttribute): void { }
    applySelectedAttribute(instance: SpanAttribute): void { }
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: double | string | Resource | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: DecorationStyleInterface | undefined
    _letterSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing_0_0value?: double | string | undefined
    _textCase_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textCase_0_0value?: TextCase | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: Length | undefined
    _textShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    _textBackgroundStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textBackgroundStyle_0_0value?: TextBackgroundStyle | undefined
    _baselineOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _baselineOffset_0_0value?: LengthMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkSpanPeer;
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined));
                }
            }
        }
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
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
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
        if (this._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineHeightAttribute((this._lineHeight_0_0value as Length | undefined));
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineHeightAttribute((undefined as Length | undefined));
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
        if (this._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextBackgroundStyleAttribute((this._textBackgroundStyle_0_0value as TextBackgroundStyle | undefined));
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextBackgroundStyleAttribute((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
        if (this._baselineOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._baselineOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBaselineOffsetAttribute((this._baselineOffset_0_0value as LengthMetrics | undefined));
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBaselineOffsetAttribute((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SpanModifier): void {
        super.mergeModifier(modifier)
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined));
                }
            }
        }
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
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
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
        if (modifier._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineHeight(modifier._lineHeight_0_0value);
                    break;
                }
                default: {
                    this.lineHeight((undefined as Length | undefined));
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
        if (modifier._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textBackgroundStyle(modifier._textBackgroundStyle_0_0value);
                    break;
                }
                default: {
                    this.textBackgroundStyle((undefined as TextBackgroundStyle | undefined));
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
                    this.baselineOffset((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
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
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        if (((this._decoration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._decoration_0_flag = AttributeUpdaterFlag.UPDATE
            this._decoration_0_0value = value
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
        } else
        {
            this._textCase_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineHeight(value: Length | undefined): this {
        if (((this._lineHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineHeight_0_0value = value
        } else
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._textShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._textShadow_0_0value = value
        } else
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (((this._textBackgroundStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textBackgroundStyle_0_0value = value
        } else
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    baselineOffset(value: LengthMetrics | undefined): this {
        if (((this._baselineOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._baselineOffset_0_0value = value
        } else
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
