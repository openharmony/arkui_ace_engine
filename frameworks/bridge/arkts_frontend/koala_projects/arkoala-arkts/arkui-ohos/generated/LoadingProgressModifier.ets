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
import { AttributeModifier, ContentModifier, hookLoadingProgressContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkLoadingProgressPeer, LoadingProgressConfiguration, LoadingProgressAttribute } from "./component/loadingProgress"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class LoadingProgressModifier extends CommonMethodModifier implements LoadingProgressAttribute,AttributeModifier<LoadingProgressAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LoadingProgressAttribute): void { }
    applyPressedAttribute(instance: LoadingProgressAttribute): void { }
    applyFocusedAttribute(instance: LoadingProgressAttribute): void { }
    applyDisabledAttribute(instance: LoadingProgressAttribute): void { }
    applySelectedAttribute(instance: LoadingProgressAttribute): void { }
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    _enableLoading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableLoading_0_0value?: boolean | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<LoadingProgressConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkLoadingProgressPeer;
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
        if (this._enableLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableLoadingAttribute((this._enableLoading_0_0value as boolean | undefined));
                    this._enableLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableLoading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableLoadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookLoadingProgressContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<LoadingProgressConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookLoadingProgressContentModifier(peer, (undefined as ContentModifier<LoadingProgressConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: LoadingProgressModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
        if (modifier._enableLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableLoading(modifier._enableLoading_0_0value);
                    break;
                }
                default: {
                    this.enableLoading((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<LoadingProgressConfiguration> | undefined));
                }
            }
        }
    }
    color(value: ResourceColor | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableLoading(value: boolean | undefined): this {
        if (((this._enableLoading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableLoading_0_0value) !== (value)))
        {
            this._enableLoading_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableLoading_0_0value = value
        } else
        {
            this._enableLoading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentModifier_0_0value) !== (value)))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
