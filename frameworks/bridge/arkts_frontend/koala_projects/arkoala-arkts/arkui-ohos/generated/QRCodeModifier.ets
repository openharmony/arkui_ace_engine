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
import { ArkQRCodePeer, QRCodeAttribute } from "./component/qrcode"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class QRCodeModifier extends CommonMethodModifier implements QRCodeAttribute,AttributeModifier<QRCodeAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: QRCodeAttribute): void { }
    applyPressedAttribute(instance: QRCodeAttribute): void { }
    applyFocusedAttribute(instance: QRCodeAttribute): void { }
    applyDisabledAttribute(instance: QRCodeAttribute): void { }
    applySelectedAttribute(instance: QRCodeAttribute): void { }
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    _backgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundColor_0_0value?: ResourceColor | undefined
    _contentOpacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentOpacity_0_0value?: double | Resource | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkQRCodePeer;
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
        if (this._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._contentOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentOpacityAttribute((this._contentOpacity_0_0value as double | Resource | undefined));
                    this._contentOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentOpacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentOpacityAttribute((undefined as double | Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: QRCodeModifier): void {
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
        if (modifier._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._contentOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentOpacity(modifier._contentOpacity_0_0value);
                    break;
                }
                default: {
                    this.contentOpacity((undefined as double | Resource | undefined));
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
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._backgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundColor_0_0value = value
        } else
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentOpacity(value: double | Resource | undefined): this {
        if (((this._contentOpacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentOpacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentOpacity_0_0value = value
        } else
        {
            this._contentOpacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
