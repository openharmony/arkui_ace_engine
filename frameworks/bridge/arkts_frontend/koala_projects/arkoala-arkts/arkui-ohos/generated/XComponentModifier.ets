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
import { ArkXComponentPeer, XComponentAttribute } from "./component/xcomponent"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { VoidCallback } from "./component/units"
export class XComponentModifier extends CommonMethodModifier implements XComponentAttribute,AttributeModifier<XComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: XComponentAttribute): void { }
    applyPressedAttribute(instance: XComponentAttribute): void { }
    applyFocusedAttribute(instance: XComponentAttribute): void { }
    applyDisabledAttribute(instance: XComponentAttribute): void { }
    applySelectedAttribute(instance: XComponentAttribute): void { }
    _onLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoad_0_0value?: VoidCallback | undefined
    _onDestroy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDestroy_0_0value?: VoidCallback | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _enableSecure_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableSecure_0_0value?: boolean | undefined
    _enableTransparentLayer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableTransparentLayer_0_0value?: boolean | undefined
    _hdrBrightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hdrBrightness_0_0value?: double | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkXComponentPeer;
        if (this._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDestroyAttribute((this._onDestroy_0_0value as VoidCallback | undefined));
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDestroyAttribute((undefined as VoidCallback | undefined));
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
        if (this._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableSecureAttribute((this._enableSecure_0_0value as boolean | undefined));
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableSecureAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableTransparentLayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableTransparentLayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableTransparentLayerAttribute((this._enableTransparentLayer_0_0value as boolean | undefined));
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableTransparentLayerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHdrBrightnessAttribute((this._hdrBrightness_0_0value as double | undefined));
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHdrBrightnessAttribute((undefined as double | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: XComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDestroy(modifier._onDestroy_0_0value);
                    break;
                }
                default: {
                    this.onDestroy((undefined as VoidCallback | undefined));
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
        if (modifier._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableSecure(modifier._enableSecure_0_0value);
                    break;
                }
                default: {
                    this.enableSecure((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableTransparentLayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableTransparentLayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableTransparentLayer(modifier._enableTransparentLayer_0_0value);
                    break;
                }
                default: {
                    this.enableTransparentLayer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hdrBrightness(modifier._hdrBrightness_0_0value);
                    break;
                }
                default: {
                    this.hdrBrightness((undefined as double | undefined));
                }
            }
        }
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._onLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoad_0_0value = value
        } else
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDestroy(value: VoidCallback | undefined): this {
        if (((this._onDestroy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDestroy_0_0value = value
        } else
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.SKIP
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
    enableSecure(value: boolean | undefined): this {
        if (((this._enableSecure_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableSecure_0_0value) !== (value)))
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableSecure_0_0value = value
        } else
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableTransparentLayer(value: boolean | undefined): this {
        if (((this._enableTransparentLayer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableTransparentLayer_0_0value) !== (value)))
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableTransparentLayer_0_0value = value
        } else
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hdrBrightness(value: double | undefined): this {
        if (((this._hdrBrightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hdrBrightness_0_0value) !== (value)))
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.UPDATE
            this._hdrBrightness_0_0value = value
        } else
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
