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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, ContentModifier, hookTextTimerContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTextTimerPeer, TimerCallback, TextTimerConfiguration, TextTimerAttribute } from './component/textTimer'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, ShadowOptions } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, ResourceStr as arkui_component_units_ResourceStr } from './component/units'
import { Color as arkui_component_enums_Color, FontStyle, FontWeight } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class TextTimerModifier extends CommonMethodModifier implements TextTimerAttribute,AttributeModifier<TextTimerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TextTimerAttribute): void { }
    applyPressedAttribute(instance: TextTimerAttribute): void { }
    applyFocusedAttribute(instance: TextTimerAttribute): void { }
    applyDisabledAttribute(instance: TextTimerAttribute): void { }
    applySelectedAttribute(instance: TextTimerAttribute): void { }
    public _format_0_0value?: string | undefined
    public _fontColor_0_0value?: ResourceColor | undefined
    public _fontSize_0_0value?: Length | undefined
    public _fontStyle_0_0value?: FontStyle | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | arkui_component_units_ResourceStr | undefined
    public _fontFamily_0_0value?: arkui_component_units_ResourceStr | undefined
    public _onTimer_0_0value?: TimerCallback | undefined
    public _textShadow_0_0value?: ShadowOptions | Array<ShadowOptions> | undefined
    public _contentModifier_0_0value?: ContentModifier<TextTimerConfiguration> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTextTimerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTextTimerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setFormatAttribute((this._format_0_0value as string | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setFormatAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | arkui_component_units_ResourceStr | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as arkui_component_units_ResourceStr | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setFontFamilyAttribute((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnTimerAttribute((this._onTimer_0_0value as TimerCallback | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnTimerAttribute((undefined as TimerCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setTextShadowAttribute((this._textShadow_0_0value as ShadowOptions | Array<ShadowOptions> | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setTextShadowAttribute((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    hookTextTimerContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<TextTimerConfiguration> | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    hookTextTimerContentModifier(peer, (undefined as ContentModifier<TextTimerConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextTimerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: TextTimerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.format(modifier._format_0_0value);
                    break;
                }
                default: {
                    this.format((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onTimer(modifier._onTimer_0_0value);
                    break;
                }
                default: {
                    this.onTimer((undefined as TimerCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.textShadow(modifier._textShadow_0_0value);
                    break;
                }
                default: {
                    this.textShadow((undefined as ShadowOptions | Array<ShadowOptions> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<TextTimerConfiguration> | undefined));
                }
            }
        }
    }
    format(value: string | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._format_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._format_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | arkui_component_units_ResourceStr | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    fontFamily(value: arkui_component_units_ResourceStr | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onTimer(value: TimerCallback | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onTimer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._textShadow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
