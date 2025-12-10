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

import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSecurityComponentMethodPeer, SecurityComponentLayoutDirection, SecurityComponentMethod } from './component/securityComponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Resource as arkui_component_units_Resource, BorderRadiuses, Padding, Length, SizeOptions, ConstraintSizeOptions } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { FontStyle, FontWeight, Color as arkui_component_enums_Color, BorderStyle, Alignment, Axis, TextHeightAdaptivePolicy } from './component/enums'
import { AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle } from './component/common'
export class SecurityComponentMethodModifier implements SecurityComponentMethod {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    public _iconSize_0_0value?: Dimension | undefined
    public _layoutDirection_0_0value?: SecurityComponentLayoutDirection | undefined
    public _position_0_0value?: Position | undefined
    public _markAnchor_0_0value?: Position | undefined
    public _offset_0_0value?: Position | Edges | LocalizedEdges | undefined
    public _fontSize_0_0value?: Dimension | undefined
    public _fontStyle_0_0value?: FontStyle | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | global_resource_Resource | undefined
    public _fontFamily_0_0value?: string | global_resource_Resource | undefined
    public _fontColor_0_0value?: ResourceColor | undefined
    public _iconColor_0_0value?: ResourceColor | undefined
    public _backgroundColor_0_0value?: ResourceColor | undefined
    public _borderStyle_0_0value?: BorderStyle | undefined
    public _borderWidth_0_0value?: Dimension | undefined
    public _borderColor_0_0value?: ResourceColor | undefined
    public _borderRadius_0_0value?: Dimension | BorderRadiuses | undefined
    public _padding_0_0value?: Padding | Dimension | undefined
    public _textIconSpace_0_0value?: Dimension | undefined
    public _key_0_0value?: string | undefined
    public _width_0_0value?: Length | undefined
    public _height_0_0value?: Length | undefined
    public _size_0_0value?: SizeOptions | undefined
    public _constraintSize_0_0value?: ConstraintSizeOptions | undefined
    public _align_0_0value?: Alignment | undefined
    public _alignRules_0_0value?: AlignRuleOption | LocalizedAlignRuleOptions | undefined
    public _id_0_0value?: string | undefined
    public _chainMode_0_0value?: Axis | undefined
    public _chainMode_0_1value?: ChainStyle | undefined
    public _minFontScale_0_0value?: double | global_resource_Resource | undefined
    public _maxFontScale_0_0value?: double | global_resource_Resource | undefined
    public _maxLines_0_0value?: int32 | global_resource_Resource | undefined
    public _minFontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _maxFontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    public _enabled_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        this._state.addRef()
        const peer = node as ArkSecurityComponentMethodPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSecurityComponentMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setIconSizeAttribute((this._iconSize_0_0value as Dimension | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setIconSizeAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as SecurityComponentLayoutDirection | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setLayoutDirectionAttribute((undefined as SecurityComponentLayoutDirection | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setPositionAttribute((this._position_0_0value as Position | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setPositionAttribute((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setMarkAnchorAttribute((this._markAnchor_0_0value as Position | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setMarkAnchorAttribute((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOffsetAttribute((this._offset_0_0value as Position | Edges | LocalizedEdges | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOffsetAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Dimension | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setFontSizeAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | global_resource_Resource | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | global_resource_Resource | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setFontFamilyAttribute((undefined as string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setIconColorAttribute((this._iconColor_0_0value as ResourceColor | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setIconColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setBorderStyleAttribute((this._borderStyle_0_0value as BorderStyle | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setBorderStyleAttribute((undefined as BorderStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setBorderWidthAttribute((this._borderWidth_0_0value as Dimension | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setBorderWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setBorderColorAttribute((this._borderColor_0_0value as ResourceColor | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setBorderRadiusAttribute((this._borderRadius_0_0value as Dimension | BorderRadiuses | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setBorderRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setPaddingAttribute((this._padding_0_0value as Padding | Dimension | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setPaddingAttribute((undefined as Padding | Dimension | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setTextIconSpaceAttribute((this._textIconSpace_0_0value as Dimension | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setTextIconSpaceAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setWidthAttribute((this._width_0_0value as Length | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setWidthAttribute((undefined as Length | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkSecurityComponentMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setHeightAttribute((this._height_0_0value as Length | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setSizeAttribute((this._size_0_0value as SizeOptions | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setConstraintSizeAttribute((this._constraintSize_0_0value as ConstraintSizeOptions | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setConstraintSizeAttribute((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setAlignAttribute((this._align_0_0value as Alignment | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setAlignAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setAlignRulesAttribute((this._alignRules_0_0value as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setAlignRulesAttribute((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setChainModeAttribute((this._chainMode_0_0value as Axis | undefined), (this._chainMode_0_1value as ChainStyle | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setChainModeAttribute((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setMinFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setMaxFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | global_resource_Resource | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setMaxLinesAttribute((undefined as int32 | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setMinFontSizeAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setMaxFontSizeAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setHeightAdaptivePolicyAttribute((this._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setEnabledAttribute((this._enabled_0_0value as boolean | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setEnabledAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SecurityComponentMethodModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: SecurityComponentMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.iconSize(modifier._iconSize_0_0value);
                    break;
                }
                default: {
                    this.iconSize((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection((undefined as SecurityComponentLayoutDirection | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.position(modifier._position_0_0value);
                    break;
                }
                default: {
                    this.position((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.markAnchor(modifier._markAnchor_0_0value);
                    break;
                }
                default: {
                    this.markAnchor((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.offset(modifier._offset_0_0value);
                    break;
                }
                default: {
                    this.offset((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
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
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
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
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.iconColor(modifier._iconColor_0_0value);
                    break;
                }
                default: {
                    this.iconColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.borderStyle(modifier._borderStyle_0_0value);
                    break;
                }
                default: {
                    this.borderStyle((undefined as BorderStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.borderWidth(modifier._borderWidth_0_0value);
                    break;
                }
                default: {
                    this.borderWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.borderColor(modifier._borderColor_0_0value);
                    break;
                }
                default: {
                    this.borderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.borderRadius(modifier._borderRadius_0_0value);
                    break;
                }
                default: {
                    this.borderRadius((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.padding(modifier._padding_0_0value);
                    break;
                }
                default: {
                    this.padding((undefined as Padding | Dimension | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.textIconSpace(modifier._textIconSpace_0_0value);
                    break;
                }
                default: {
                    this.textIconSpace((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.width(modifier._width_0_0value);
                    break;
                }
                default: {
                    this.width((undefined as Length | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: SecurityComponentMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.height(modifier._height_0_0value);
                    break;
                }
                default: {
                    this.height((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.constraintSize(modifier._constraintSize_0_0value);
                    break;
                }
                default: {
                    this.constraintSize((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.align(modifier._align_0_0value);
                    break;
                }
                default: {
                    this.align((undefined as Alignment | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.alignRules(modifier._alignRules_0_0value);
                    break;
                }
                default: {
                    this.alignRules((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.chainMode(modifier._chainMode_0_0value, modifier._chainMode_0_1value);
                    break;
                }
                default: {
                    this.chainMode((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.heightAdaptivePolicy(modifier._heightAdaptivePolicy_0_0value);
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.enabled(modifier._enabled_0_0value);
                    break;
                }
                default: {
                    this.enabled((undefined as boolean | undefined));
                }
            }
        }
    }
    iconSize(value: Dimension | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._iconSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._layoutDirection_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    position(value: Position | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._position_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    markAnchor(value: Position | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._markAnchor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._offset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    fontSize(value: Dimension | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    fontFamily(value: string | global_resource_Resource | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    iconColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._iconColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    borderStyle(value: BorderStyle | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._borderStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    borderWidth(value: Dimension | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._borderWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    borderColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._borderColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._borderRadius_0_0value = radius
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    padding(value: Padding | Dimension | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._padding_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    textIconSpace(value: Dimension | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._textIconSpace_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._flagArray[18]) == (0)) || ((this._key_0_0value) !== (value))) {
            this._flagArray[18] = 1
            this._key_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    width(value: Length | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._width_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    height(value: Length | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._height_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    size(value: SizeOptions | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._size_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._constraintSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    align(alignType: Alignment | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._align_0_0value = alignType
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    alignRules(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._alignRules_0_0value = alignRule
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    id(description: string | undefined): this {
        if (((this._flagArray[25]) == (0)) || ((this._id_0_0value) !== (description))) {
            this._flagArray[25] = 1
            this._id_0_0value = description
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true) || (true)) {
            this._flagArray[26] = 1
            this._chainMode_0_0value = direction
            this._chainMode_0_1value = style
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    minFontScale(scale: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true)) {
            this._flagArray[27] = 1
            this._minFontScale_0_0value = scale
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    maxFontScale(scale: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._maxFontScale_0_0value = scale
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    maxLines(line: int32 | global_resource_Resource | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true)) {
            this._flagArray[29] = 1
            this._maxLines_0_0value = line
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    minFontSize(minSize: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true)) {
            this._flagArray[30] = 1
            this._minFontSize_0_0value = minSize
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    maxFontSize(maxSize: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true)) {
            this._flagArray[31] = 1
            this._maxFontSize_0_0value = maxSize
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._heightAdaptivePolicy_0_0value = policy
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    enabled(respond: boolean | undefined): this {
        if (((this._flagArray[33]) == (0)) || ((this._enabled_0_0value) !== (respond))) {
            this._flagArray[33] = 1
            this._enabled_0_0value = respond
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
