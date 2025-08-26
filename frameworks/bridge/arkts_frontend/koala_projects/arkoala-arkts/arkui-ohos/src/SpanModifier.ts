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

import { ArkSpanPeer, SpanAttribute } from "./component/span"
import { AttributeModifier, ShadowOptions, CommonMethod } from "./component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from "./CommonMethodModifier"
import { BaseSpanModifier } from "./BaseSpanModifier"
import { Font, ResourceColor, Length } from "./component/units"
import { FontStyle, TextCase } from "./component/enums"
import { Resource } from "global.resource"
import { DecorationStyleInterface } from "./component/styledString"
import { PeerNode } from "./PeerNode"

export class SpanModifier extends BaseSpanModifier implements SpanAttribute,AttributeModifier<SpanAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: SpanAttribute): void { }
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: number | string | Resource | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: DecorationStyleInterface | undefined
    _textCase_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textCase_0_0value?: TextCase | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: Length | undefined
    _textShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer: ArkSpanPeer = value as ArkSpanPeer
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontSizeAttribute((this._fontSize_0_0value as number | string | Resource | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontSizeAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.decorationAttribute((this._decoration_0_0value as DecorationStyleInterface | undefined));
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.decorationAttribute((undefined as DecorationStyleInterface | undefined));
                }
            }
        }
        if (this._textCase_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textCase_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textCaseAttribute((this._textCase_0_0value as TextCase | undefined));
                    this._textCase_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textCase_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textCase_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textCaseAttribute((undefined as TextCase | undefined));
                }
            }
        }
        if (this._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lineHeightAttribute((this._lineHeight_0_0value as Length | undefined));
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lineHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._textShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textShadowAttribute((this._textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    this._textShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textShadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textShadowAttribute((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof SpanModifier)) {
            return
        }
        const modifier = value as SpanModifier;
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
                    this.fontSize((undefined as number | string | Resource | undefined));
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
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._font_0_0value !== value || !Type.of(value).isPrimitive())
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
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontColor_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: number | string | Resource | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontSize_0_0value !== value || !Type.of(value).isPrimitive())
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
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontStyle_0_0value !== value)
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontFamily_0_0value !== value || !Type.of(value).isPrimitive())
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
        if (((this._decoration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._decoration_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._decoration_0_flag = AttributeUpdaterFlag.UPDATE
            this._decoration_0_0value = value
        } else
        {
            this._decoration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textCase(value: TextCase | undefined): this {
        if (((this._textCase_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textCase_0_0value !== value)
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
        if (((this._lineHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._lineHeight_0_0value !== value || !Type.of(value).isPrimitive())
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
        if (((this._textShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._textShadow_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._textShadow_0_0value = value
        } else
        {
            this._textShadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
