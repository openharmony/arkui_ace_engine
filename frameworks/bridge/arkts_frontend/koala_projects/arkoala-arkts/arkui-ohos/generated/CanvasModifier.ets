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
import { ArkCanvasPeer, DrawingRenderingContext, CanvasAttribute } from "./component/canvas"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { VoidCallback } from "./component/units"
export class CanvasModifier extends CommonMethodModifier implements CanvasAttribute,AttributeModifier<CanvasAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CanvasAttribute): void { }
    applyPressedAttribute(instance: CanvasAttribute): void { }
    applyFocusedAttribute(instance: CanvasAttribute): void { }
    applyDisabledAttribute(instance: CanvasAttribute): void { }
    applySelectedAttribute(instance: CanvasAttribute): void { }
    _onReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReady_0_0value?: VoidCallback | ((value0: DrawingRenderingContext | undefined) => void) | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkCanvasPeer;
        if (this._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as VoidCallback | ((value0: DrawingRenderingContext | undefined) => void) | undefined));
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReadyAttribute((undefined as VoidCallback | ((value0: DrawingRenderingContext | undefined) => void) | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CanvasModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as VoidCallback | ((value0: DrawingRenderingContext | undefined) => void) | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
    }
    onReady(value: VoidCallback | ((value0: DrawingRenderingContext | undefined) => void) | undefined): this {
        if (((this._onReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReady_0_0value = value
        } else
        {
            this._onReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
