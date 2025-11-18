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
import { ArkBaseSpanPeer, TextBackgroundStyle, BaseSpan } from "./component/span"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { LengthMetrics } from "arkui.Graphics"
export class BaseSpanModifier extends CommonMethodModifier implements BaseSpan,AttributeModifier<BaseSpan> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: BaseSpan): void { }
    applyPressedAttribute(instance: BaseSpan): void { }
    applyFocusedAttribute(instance: BaseSpan): void { }
    applyDisabledAttribute(instance: BaseSpan): void { }
    applySelectedAttribute(instance: BaseSpan): void { }
    _textBackgroundStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textBackgroundStyle_0_0value?: TextBackgroundStyle | undefined
    _baselineOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _baselineOffset_0_0value?: LengthMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkBaseSpanPeer;
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
    mergeModifier(modifier: BaseSpanModifier): void {
        super.mergeModifier(modifier)
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
    public attributeModifier(value: AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
