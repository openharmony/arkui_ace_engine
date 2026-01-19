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
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkDividerPeer, DividerAttribute } from "./component/divider"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color, LineCapStyle } from "./component/enums"
import { Resource } from "global.resource"
export class DividerModifier extends CommonMethodModifier implements DividerAttribute,AttributeModifier<DividerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: DividerAttribute): void { }
    applyPressedAttribute(instance: DividerAttribute): void { }
    applyFocusedAttribute(instance: DividerAttribute): void { }
    applyDisabledAttribute(instance: DividerAttribute): void { }
    applySelectedAttribute(instance: DividerAttribute): void { }
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: number | string | undefined
    _lineCap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineCap_0_0value?: LineCapStyle | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkDividerPeer;
        if (this._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._vertical_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as number | string | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeWidthAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._lineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineCapAttribute((this._lineCap_0_0value as LineCapStyle | undefined));
                    this._lineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineCap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineCapAttribute((undefined as LineCapStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: DividerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._lineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineCap(modifier._lineCap_0_0value);
                    break;
                }
                default: {
                    this.lineCap((undefined as LineCapStyle | undefined));
                }
            }
        }
    }
    vertical(value: boolean | undefined): this {
        if (((this._vertical_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._vertical_0_0value) !== (value)))
        {
            this._vertical_0_flag = AttributeUpdaterFlag.UPDATE
            this._vertical_0_0value = value
            this._state.fireChange()
        } else
        {
            this._vertical_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    color(value: ResourceColor | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
            this._state.fireChange()
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: number | string | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeWidth_0_0value) !== (value)))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineCap(value: LineCapStyle | undefined): this {
        if (((this._lineCap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineCap_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineCap_0_0value = value
            this._state.fireChange()
        } else
        {
            this._lineCap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
