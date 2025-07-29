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

import { int32 } from '@koalaui/common'
import { AttributeModifier } from 'arkui/component/common';
import { SymbolGlyphAttribute } from 'arkui/component/symbolglyph';
import { RuntimeType, runtimeType } from "@koalaui/interop";

import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode';
import { ArkSymbolGlyphPeer, SymbolEffect, SymbolEffectStrategy, SymbolRenderingStrategy } from './component/symbolglyph';
import { FontWeight } from './component/enums';
import { ResourceColor } from "./component/units";
import { Resource } from 'global.resource';

export class SymbolGlyphModifier extends CommonMethodModifier implements SymbolGlyphAttribute, AttributeModifier<SymbolGlyphAttribute> {
    constructor(src?: Resource) {
        super()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (RuntimeType.UNDEFINED != src_type) {
            this.setSymbolGlyphOptions(src)
        }
    }

    applyNormalAttribute(instance: SymbolGlyphAttribute): void { }
    applyPressedAttribute(instance: SymbolGlyphAttribute): void { }
    applyFocusedAttribute(instance: SymbolGlyphAttribute): void { }
    applyDisabledAttribute(instance: SymbolGlyphAttribute): void { }
    applySelectedAttribute(instance: SymbolGlyphAttribute): void { }

    _setSymbolGlyphOptions_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setSymbolGlyphOptions0_value?: Resource | undefined
    _fontSize_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize0_value?: number | string | Resource | undefined
    _fontColor_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor0_value?: Array<ResourceColor> | undefined
    _fontWeight_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight0_value?: number | FontWeight | string | undefined
    _effectStrategy_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectStrategy0_value?: SymbolEffectStrategy | undefined
    _renderingStrategy_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderingStrategy0_value?: SymbolRenderingStrategy | undefined
    _minFontScale_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale0_value?: number | Resource | undefined
    _symbolEffect_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _symbolEffect0_value?: SymbolEffect | undefined
    _symbolEffect1_value?: boolean | number | undefined

    public setSymbolGlyphOptions(value: Resource | undefined): this {
        if (this._setSymbolGlyphOptions_flag === AttributeUpdaterFlag.INITIAL ||
            this._setSymbolGlyphOptions0_value !== value || !Type.of(value).isPrimitive()) {
            this._setSymbolGlyphOptions0_value = value
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontSize(value: number | string | Resource | undefined): this {
        if (this._fontSize_flag === AttributeUpdaterFlag.INITIAL ||
            this._fontSize0_value !== value || !Type.of(value).isPrimitive()) {
            this._fontSize0_value = value
            this._fontSize_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._fontSize_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this._fontColor_flag === AttributeUpdaterFlag.INITIAL ||
            this._fontColor0_value !== value || !Type.of(value).isPrimitive()) {
            this._fontColor0_value = value
            this._fontColor_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._fontColor_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this._fontWeight_flag === AttributeUpdaterFlag.INITIAL || this._fontWeight0_value !== value) {
            this._fontWeight0_value = value
            this._fontWeight_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._fontWeight_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this._effectStrategy_flag === AttributeUpdaterFlag.INITIAL || this._effectStrategy0_value !== value) {
            this._effectStrategy0_value = value
            this._effectStrategy_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._effectStrategy_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this._renderingStrategy_flag === AttributeUpdaterFlag.INITIAL || this._renderingStrategy0_value !== value) {
            this._renderingStrategy0_value = value
            this._renderingStrategy_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._renderingStrategy_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public minFontScale(value: number | Resource | undefined): this {
        if (this._minFontScale_flag === AttributeUpdaterFlag.INITIAL ||
            this._minFontScale0_value !== value || !Type.of(value).isPrimitive()) {
            this._minFontScale0_value = value
            this._minFontScale_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._minFontScale_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public maxFontScale(value: number | Resource | undefined): this {
        if (this._maxFontScale_flag === AttributeUpdaterFlag.INITIAL ||
            this._maxFontScale0_value !== value || !Type.of(value).isPrimitive()) {
            this._maxFontScale0_value = value
            this._maxFontScale_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._maxFontScale_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: boolean | number): this {
        if (this._symbolEffect_flag === AttributeUpdaterFlag.INITIAL || this._symbolEffect0_value !== symbolEffect ||
            this._symbolEffect1_value !== isActive || !Type.of(symbolEffect).isPrimitive()) {
            this._symbolEffect0_value = symbolEffect
            this._symbolEffect1_value = isActive
            this._symbolEffect_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._symbolEffect_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peerNode: ArkSymbolGlyphPeer = value as ArkSymbolGlyphPeer
        if (this._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setSymbolGlyphOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.setSymbolGlyphOptionsAttribute((this._setSymbolGlyphOptions0_value as Resource | undefined))
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.setSymbolGlyphOptionsAttribute(undefined)
                }
            }
        }
        if (this._fontSize_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._fontSize_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontSizeAttribute((this._fontSize0_value as number | string | Resource | undefined))
                    this._fontSize_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._fontSize_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontSizeAttribute(undefined)
                }
            }
        }
        if (this._fontColor_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._fontColor_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontColorAttribute((this._fontColor0_value as Array<ResourceColor> | undefined))
                    this._fontColor_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._fontColor_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontColorAttribute(undefined)
                }
            }
        }
        if (this._fontWeight_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._fontWeight_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontWeightAttribute((this._fontWeight0_value as number | FontWeight | string | undefined))
                    this._fontWeight_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._fontWeight_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontWeightAttribute(undefined)
                }
            }
        }
        if (this._effectStrategy_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._effectStrategy_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.effectStrategyAttribute((this._effectStrategy0_value as SymbolEffectStrategy | undefined))
                    this._effectStrategy_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectStrategy_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._effectStrategy_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.effectStrategyAttribute(undefined)
                }
            }
        }
        if (this._renderingStrategy_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._renderingStrategy_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.renderingStrategyAttribute((this._renderingStrategy0_value as SymbolRenderingStrategy | undefined))
                    this._renderingStrategy_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderingStrategy_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._renderingStrategy_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.renderingStrategyAttribute(undefined)
                }
            }
        }
        if (this._minFontScale_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._minFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.minFontScaleAttribute((this._minFontScale0_value as number | Resource | undefined))
                    this._minFontScale_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._minFontScale_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.minFontScaleAttribute(undefined)
                }
            }
        }
        if (this._maxFontScale_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._maxFontScale_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.maxFontScaleAttribute((this._maxFontScale0_value as number | Resource | undefined))
                    this._maxFontScale_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._maxFontScale_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.maxFontScaleAttribute(undefined)
                }
            }
        }
        if (this._symbolEffect_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._symbolEffect_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (RuntimeType.BOOLEAN == this._symbolEffect1_value) {
                        const symbolEffect_casted = this._symbolEffect0_value as (SymbolEffect | undefined)
                        const isActive_casted = this._symbolEffect1_value as Object as (boolean | undefined)
                        peerNode.symbolEffect0Attribute(symbolEffect_casted, isActive_casted)
                    } else if (RuntimeType.NUMBER == this._symbolEffect1_value) {
                        const symbolEffect_casted = this._symbolEffect0_value as (SymbolEffect | undefined)
                        const triggerValue_casted = this._symbolEffect1_value as Object as (number | undefined)
                        peerNode.symbolEffect1Attribute(symbolEffect_casted, triggerValue_casted)
                    } else {
                        const symbolEffect_casted = this._symbolEffect0_value as (SymbolEffect | undefined)
                        peerNode.symbolEffect0Attribute(symbolEffect_casted, undefined)
                    }
                    this._symbolEffect_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._symbolEffect_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._symbolEffect_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.symbolEffect0Attribute(undefined, undefined)
                }
            }
        }
    }

    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (value instanceof SymbolGlyphModifier) {
            const symbolGlyphModifier = value as SymbolGlyphModifier;
            if (symbolGlyphModifier._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._setSymbolGlyphOptions_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.setSymbolGlyphOptions(symbolGlyphModifier._setSymbolGlyphOptions0_value)
                        break
                    }
                    default: {
                        this.setSymbolGlyphOptions(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._fontSize_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._fontSize_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.fontSize(symbolGlyphModifier._fontSize0_value)
                        break
                    }
                    default: {
                        this.fontSize(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._fontColor_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._fontColor_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.fontColor(symbolGlyphModifier._fontColor0_value)
                        break
                    }
                    default: {
                        this.fontColor(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._fontWeight_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._fontWeight_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.fontWeight(symbolGlyphModifier._fontWeight0_value)
                        break
                    }
                    default: {
                        this.fontWeight(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._effectStrategy_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._effectStrategy_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.effectStrategy(symbolGlyphModifier._effectStrategy0_value)
                        break
                    }
                    default: {
                        this.effectStrategy(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._renderingStrategy_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._renderingStrategy_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.renderingStrategy(symbolGlyphModifier._renderingStrategy0_value)
                        break
                    }
                    default: {
                        this.renderingStrategy(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._minFontScale_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._minFontScale_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.minFontScale(symbolGlyphModifier._minFontScale0_value)
                        break
                    }
                    default: {
                        this.minFontScale(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._maxFontScale_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._maxFontScale_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.maxFontScale(symbolGlyphModifier._maxFontScale0_value)
                        break
                    }
                    default: {
                        this.maxFontScale(undefined)
                    }
                }
            }
            if (symbolGlyphModifier._symbolEffect_flag !== AttributeUpdaterFlag.INITIAL) {
                switch (symbolGlyphModifier._symbolEffect_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.symbolEffect(symbolGlyphModifier._symbolEffect0_value, symbolGlyphModifier._symbolEffect1_value)
                        break
                    }
                    default: {
                        this.symbolEffect(undefined, undefined)
                    }
                }
            }
        }
    }
}