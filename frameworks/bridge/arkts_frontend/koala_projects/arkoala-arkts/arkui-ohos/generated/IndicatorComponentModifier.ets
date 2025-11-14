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
import { ArkIndicatorComponentPeer, IndicatorComponentAttribute } from "./component/indicatorcomponent"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { DotIndicator, DigitIndicator } from "./component/swiper"
export class IndicatorComponentModifier extends CommonMethodModifier implements IndicatorComponentAttribute,AttributeModifier<IndicatorComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: IndicatorComponentAttribute): void { }
    applyPressedAttribute(instance: IndicatorComponentAttribute): void { }
    applyFocusedAttribute(instance: IndicatorComponentAttribute): void { }
    applyDisabledAttribute(instance: IndicatorComponentAttribute): void { }
    applySelectedAttribute(instance: IndicatorComponentAttribute): void { }
    _initialIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _initialIndex_0_0value?: int32 | undefined
    _count_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _count_0_0value?: int32 | undefined
    _style_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _style_0_0value?: DotIndicator | DigitIndicator | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: int32) => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkIndicatorComponentPeer;
        if (this._initialIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._initialIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInitialIndexAttribute((this._initialIndex_0_0value as int32 | undefined));
                    this._initialIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInitialIndexAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._count_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._count_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCountAttribute((this._count_0_0value as int32 | undefined));
                    this._count_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._count_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._count_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCountAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStyleAttribute((this._style_0_0value as DotIndicator | DigitIndicator | undefined));
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._style_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._style_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStyleAttribute((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (this._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._loop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
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
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: int32) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: IndicatorComponentModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._initialIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._initialIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialIndex(modifier._initialIndex_0_0value);
                    break;
                }
                default: {
                    this.initialIndex((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._count_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._count_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.count(modifier._count_0_0value);
                    break;
                }
                default: {
                    this.count((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._style_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._style_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.style(modifier._style_0_0value);
                    break;
                }
                default: {
                    this.style((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (modifier._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
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
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
    }
    initialIndex(value: int32 | undefined): this {
        if (((this._initialIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._initialIndex_0_0value) !== (value)))
        {
            this._initialIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._initialIndex_0_0value = value
            this._state.fireChange()
        } else
        {
            this._initialIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    count(value: int32 | undefined): this {
        if (((this._count_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._count_0_0value) !== (value)))
        {
            this._count_0_flag = AttributeUpdaterFlag.UPDATE
            this._count_0_0value = value
            this._state.fireChange()
        } else
        {
            this._count_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    style(value: DotIndicator | DigitIndicator | undefined): this {
        if (((this._style_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._style_0_flag = AttributeUpdaterFlag.UPDATE
            this._style_0_0value = value
            this._state.fireChange()
        } else
        {
            this._style_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._loop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._loop_0_0value) !== (value)))
        {
            this._loop_0_flag = AttributeUpdaterFlag.UPDATE
            this._loop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._loop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
    onChange(value: ((value0: int32) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
