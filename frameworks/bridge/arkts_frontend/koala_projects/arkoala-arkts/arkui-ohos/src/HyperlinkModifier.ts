/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from '@koalaui/common';
import { KPointer, RuntimeType, runtimeType } from '@koalaui/interop';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';

import { AttributeModifier, CommonMethod } from './component/common'
import { Color } from './component/enums'
import { Resource } from 'global.resource'
import { HyperlinkAttribute, ArkHyperlinkPeer } from './component/hyperlink'
import { PeerNode } from './PeerNode';

export class HyperlinkModifier extends CommonMethodModifier implements HyperlinkAttribute, AttributeModifier<HyperlinkAttribute> {

    applyNormalAttribute(instance: HyperlinkAttribute): void { }
    applyPressedAttribute(instance: HyperlinkAttribute): void { }
    applyFocusedAttribute(instance: HyperlinkAttribute): void { }
    applyDisabledAttribute(instance: HyperlinkAttribute): void { }
    applySelectedAttribute(instance: HyperlinkAttribute): void { }

    _setHyperlinkOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setHyperlinkOptions_0_0value?: string | Resource
    _setHyperlinkOptions_0_1value?: string | Resource
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: Color | number | string | Resource | undefined

    public setHyperlinkOptions(address: string | Resource, content?: string | Resource): this {
        if (((this._setHyperlinkOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._setHyperlinkOptions_0_0value !== address || this._setHyperlinkOptions_0_1value !== content)
        {
            this._setHyperlinkOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._setHyperlinkOptions_0_0value = address
            this._setHyperlinkOptions_0_1value = content
        } else
        {
            this._setHyperlinkOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public color(value: Color | number | string | Resource | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._color_0_0value !== value)
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer: ArkHyperlinkPeer = peerNode as ArkHyperlinkPeer
        if (this._setHyperlinkOptions_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setHyperlinkOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHyperlinkOptionsAttribute(this._setHyperlinkOptions_0_0value as string | Resource,
                        this._setHyperlinkOptions_0_1value as string | Resource | undefined)
                    this._setHyperlinkOptions_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setHyperlinkOptions_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setHyperlinkOptions_0_flag = AttributeUpdaterFlag.INITIAL
                    peer.setHyperlinkOptionsAttribute('', undefined)
                }
            }
        }
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.colorAttribute((this._color_0_0value as Color | number | string | Resource | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.colorAttribute((undefined as Color | number | string | Resource | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof HyperlinkModifier)) {
            return
        }
        const modifier = value as HyperlinkModifier
        if (modifier._setHyperlinkOptions_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setHyperlinkOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    if (modifier._setHyperlinkOptions_0_0value !== undefined) {
                        this.setHyperlinkOptions(modifier._setHyperlinkOptions_0_0value! as string | Resource,
                            modifier._setHyperlinkOptions_0_1value)
                    }
                    break
                }
                default: {
                    this.setHyperlinkOptions('', undefined)
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
                    this.color((undefined as Color | number | string | Resource | undefined));
                }
            }
        }
    }
}