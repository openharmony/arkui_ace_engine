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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSymbolSpanPeer, SymbolSpanAttribute } from "./component/symbolSpan"
import { int32 } from "@koalaui/common"
import { Resource } from "global.resource"
import { ResourceColor } from "./component/units"
import { Color, FontWeight } from "./component/enums"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./component/symbolglyph"
import { RuntimeType, runtimeType } from "@koalaui/interop"
import { ModifierState } from "./CommonModifier"
export class SymbolSpanModifier implements SymbolSpanAttribute,AttributeModifier<SymbolSpanAttribute> {
    constructor(src?: Resource) {
        super()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (RuntimeType.UNDEFINED != src_type) {
            this.setSymbolSpanOptions(src)
        }
    }
    _instanceId: number = -1;
     _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SymbolSpanAttribute): void { }
    applyPressedAttribute(instance: SymbolSpanAttribute): void { }
    applyFocusedAttribute(instance: SymbolSpanAttribute): void { }
    applyDisabledAttribute(instance: SymbolSpanAttribute): void { }
    applySelectedAttribute(instance: SymbolSpanAttribute): void { }
    _setSymbolSpanOptions_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setSymbolSpanOptions0_value?: Resource | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: double | string | Resource | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: Array<ResourceColor> | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _effectStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectStrategy_0_0value?: SymbolEffectStrategy | undefined
    _renderingStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    _key_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _key_0_0value?: string | undefined
    _id_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _id_0_0value?: string | undefined
    applyModifierPatch(node: PeerNode): void {
        const peer = node as ArkSymbolSpanPeer;
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
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as Array<ResourceColor> | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as Array<ResourceColor> | undefined));
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
        if (this._effectStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._effectStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEffectStrategyAttribute((this._effectStrategy_0_0value as SymbolEffectStrategy | undefined));
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEffectStrategyAttribute((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (this._renderingStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderingStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderingStrategyAttribute((this._renderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderingStrategyAttribute((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (this._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._key_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._id_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SymbolSpanModifier): void {
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
                    this.fontSize((undefined as double | string | Resource | undefined));
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
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
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
        if (modifier._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (modifier._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
    }
    setSymbolSpanOptions(value: Resource | undefined): this {
        if (this._setSymbolSpanOptions_flag === AttributeUpdaterFlag.INITIAL ||
            this._setSymbolSpanOptions0_value !== value || !Type.of(value).isPrimitive()) {
            this._setSymbolSpanOptions0_value = value
            this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._setSymbolSpanOptions_flag = AttributeUpdaterFlag.SKIP
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
    fontColor(value: Array<ResourceColor> | undefined): this {
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
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (((this._effectStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._renderingStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderingStrategy_0_0value = value
        } else
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._key_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._key_0_0value) !== (value)))
        {
            this._key_0_flag = AttributeUpdaterFlag.UPDATE
            this._key_0_0value = value
        } else
        {
            this._key_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    id(value: string | undefined): this {
        if (((this._id_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._id_0_0value) !== (value)))
        {
            this._id_0_flag = AttributeUpdaterFlag.UPDATE
            this._id_0_0value = value
        } else
        {
            this._id_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}
