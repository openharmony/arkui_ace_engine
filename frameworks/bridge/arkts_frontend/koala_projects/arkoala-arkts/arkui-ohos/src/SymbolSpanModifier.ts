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

import { int32, int64, float32 } from "@koalaui/common"
import { KPointer, RuntimeType, runtimeType } from "@koalaui/interop"
import { ArkSymbolSpanPeer } from "./component/symbolSpan"
import { AttributeModifier, CommonMethod } from "./component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier'
import { Resource } from "global.resource"
import { ResourceColor } from "./component/units"
import { FontWeight } from "./component/enums"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./component/symbolglyph"
import { SymbolSpanAttribute } from "./component/symbolSpan"
import { PeerNode } from "./PeerNode"

export class SymbolSpanModifier extends CommonMethodModifier implements SymbolSpanAttribute,AttributeModifier<SymbolSpanAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    constructor(src?: Resource) {
        super()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (RuntimeType.UNDEFINED != src_type) {
            this.setSymbolSpanOptions(src)
        }
    }
    applyNormalAttribute(instance: SymbolSpanAttribute): void { }
    _setSymbolSpanOptions_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setSymbolSpanOptions0_value?: Resource | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: number | string | Resource | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: Array<ResourceColor> | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: number | FontWeight | string | undefined
    _effectStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectStrategy_0_0value?: SymbolEffectStrategy | undefined
    _renderingStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer: ArkSymbolSpanPeer = value as ArkSymbolSpanPeer
        if (this._setSymbolSpanOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setSymbolSpanOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolSpanOptionsAttribute((this._setSymbolSpanOptions0_value! as Resource))
                    this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.INITIAL
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
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor_0_0value as Array<ResourceColor> | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontWeightAttribute((this._fontWeight_0_0value as number | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontWeightAttribute((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (this._effectStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._effectStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.effectStrategyAttribute((this._effectStrategy_0_0value as SymbolEffectStrategy | undefined));
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.effectStrategyAttribute((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (this._renderingStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderingStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.renderingStrategyAttribute((this._renderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.renderingStrategyAttribute((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof SymbolSpanModifier)) {
            return
        }
        const modifier = value as SymbolSpanModifier;
        if (modifier._setSymbolSpanOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setSymbolSpanOptions_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setSymbolSpanOptions(modifier._setSymbolSpanOptions0_value!)
                    break
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
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as Array<ResourceColor> | undefined));
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
                    this.fontWeight((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._effectStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._effectStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.effectStrategy(modifier._effectStrategy_0_0value);
                    break;
                }
                default: {
                    this.effectStrategy((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (modifier._renderingStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderingStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderingStrategy(modifier._renderingStrategy_0_0value);
                    break;
                }
                default: {
                    this.renderingStrategy((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
    }
    public setSymbolSpanOptions(value: Resource | undefined): this {
        if (this._setSymbolSpanOptions_flag === AttributeUpdaterFlag.INITIAL ||
            this._setSymbolSpanOptions0_value !== value || !Type.of(value).isPrimitive()) {
            this._setSymbolSpanOptions0_value = value
            this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.SKIP
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
    fontColor(value: Array<ResourceColor> | undefined): this {
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
    fontWeight(value: number | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._fontWeight_0_0value !== value)
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (((this._effectStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._effectStrategy_0_0value !== value)
        {
            this._effectStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._effectStrategy_0_0value = value
        } else
        {
            this._effectStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (((this._renderingStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._renderingStrategy_0_0value !== value)
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderingStrategy_0_0value = value
        } else
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
