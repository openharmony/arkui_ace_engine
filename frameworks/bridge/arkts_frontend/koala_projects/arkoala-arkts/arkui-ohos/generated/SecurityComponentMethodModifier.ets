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

import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSecurityComponentMethodPeer, SecurityComponentLayoutDirection, SecurityComponentMethod } from "./component/securityComponent"
import { int32 } from "@koalaui/common"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, BorderRadiuses, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./component/units"
import { Resource } from "global.resource"
import { FontStyle, FontWeight, Color, BorderStyle, Alignment, Axis, TextHeightAdaptivePolicy } from "./component/enums"
import { AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle } from "./component/common"
import { ModifierState } from './CommonModifier'
export class SecurityComponentMethodModifier implements SecurityComponentMethod,AttributeModifier<SecurityComponentMethod> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SecurityComponentMethod): void { }
    applyPressedAttribute(instance: SecurityComponentMethod): void { }
    applyFocusedAttribute(instance: SecurityComponentMethod): void { }
    applyDisabledAttribute(instance: SecurityComponentMethod): void { }
    applySelectedAttribute(instance: SecurityComponentMethod): void { }
    _iconSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iconSize_0_0value?: Dimension | undefined
    _layoutDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutDirection_0_0value?: SecurityComponentLayoutDirection | undefined
    _position_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _position_0_0value?: Position | undefined
    _markAnchor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _markAnchor_0_0value?: Position | undefined
    _offset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _offset_0_0value?: Position | Edges | LocalizedEdges | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: Dimension | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | Resource | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _iconColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iconColor_0_0value?: ResourceColor | undefined
    _backgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundColor_0_0value?: ResourceColor | undefined
    _borderStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderStyle_0_0value?: BorderStyle | undefined
    _borderWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderWidth_0_0value?: Dimension | undefined
    _borderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderColor_0_0value?: ResourceColor | undefined
    _borderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderRadius_0_0value?: Dimension | BorderRadiuses | undefined
    _padding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _padding_0_0value?: Padding | Dimension | undefined
    _textIconSpace_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIconSpace_0_0value?: Dimension | undefined
    _key_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _key_0_0value?: string | undefined
    _width_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _width_0_0value?: Length | undefined
    _height_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _height_0_0value?: Length | undefined
    _size_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _size_0_0value?: SizeOptions | undefined
    _constraintSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _constraintSize_0_0value?: ConstraintSizeOptions | undefined
    _align_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _align_0_0value?: Alignment | undefined
    _alignRules_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignRules_0_0value?: AlignRuleOption | LocalizedAlignRuleOptions | undefined
    _id_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _id_0_0value?: string | undefined
    _chainMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainMode_0_0value?: Axis | undefined
    _chainMode_0_1value?: ChainStyle | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: double | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: double | Resource | undefined
    _maxLines_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLines_0_0value?: int32 | Resource | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: double | string | Resource | undefined
    _maxFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize_0_0value?: double | string | Resource | undefined
    _heightAdaptivePolicy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _heightAdaptivePolicy_0_0value?: TextHeightAdaptivePolicy | undefined
    _enabled_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enabled_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        const peer = node as ArkSecurityComponentMethodPeer;
        if (this._iconSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iconSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIconSizeAttribute((this._iconSize_0_0value as Dimension | undefined));
                    this._iconSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iconSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iconSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIconSizeAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as SecurityComponentLayoutDirection | undefined));
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutDirectionAttribute((undefined as SecurityComponentLayoutDirection | undefined));
                }
            }
        }
        if (this._position_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._position_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPositionAttribute((this._position_0_0value as Position | undefined));
                    this._position_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._position_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._position_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPositionAttribute((undefined as Position | undefined));
                }
            }
        }
        if (this._markAnchor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._markAnchor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarkAnchorAttribute((this._markAnchor_0_0value as Position | undefined));
                    this._markAnchor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._markAnchor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._markAnchor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarkAnchorAttribute((undefined as Position | undefined));
                }
            }
        }
        if (this._offset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._offset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOffsetAttribute((this._offset_0_0value as Position | Edges | LocalizedEdges | undefined));
                    this._offset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._offset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._offset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOffsetAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Dimension | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | Resource | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | Resource | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._iconColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iconColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIconColorAttribute((this._iconColor_0_0value as ResourceColor | undefined));
                    this._iconColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iconColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iconColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIconColorAttribute((undefined as ResourceColor | undefined));
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
        if (this._borderStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderStyleAttribute((this._borderStyle_0_0value as BorderStyle | undefined));
                    this._borderStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderStyleAttribute((undefined as BorderStyle | undefined));
                }
            }
        }
        if (this._borderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderWidthAttribute((this._borderWidth_0_0value as Dimension | undefined));
                    this._borderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._borderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderColorAttribute((this._borderColor_0_0value as ResourceColor | undefined));
                    this._borderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._borderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderRadiusAttribute((this._borderRadius_0_0value as Dimension | BorderRadiuses | undefined));
                    this._borderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (this._padding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._padding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPaddingAttribute((this._padding_0_0value as Padding | Dimension | undefined));
                    this._padding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._padding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._padding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPaddingAttribute((undefined as Padding | Dimension | undefined));
                }
            }
        }
        if (this._textIconSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textIconSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextIconSpaceAttribute((this._textIconSpace_0_0value as Dimension | undefined));
                    this._textIconSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIconSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIconSpace_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextIconSpaceAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._key_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._width_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._width_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWidthAttribute((this._width_0_0value as Length | undefined));
                    this._width_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._width_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._width_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._height_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._height_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHeightAttribute((this._height_0_0value as Length | undefined));
                    this._height_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._height_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._height_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSizeAttribute((this._size_0_0value as SizeOptions | undefined));
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._size_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (this._constraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._constraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setConstraintSizeAttribute((this._constraintSize_0_0value as ConstraintSizeOptions | undefined));
                    this._constraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._constraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._constraintSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setConstraintSizeAttribute((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (this._align_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._align_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignAttribute((this._align_0_0value as Alignment | undefined));
                    this._align_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._align_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._align_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (this._alignRules_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignRules_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignRulesAttribute((this._alignRules_0_0value as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                    this._alignRules_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignRules_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignRules_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignRulesAttribute((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (this._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._id_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._chainMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainModeAttribute((this._chainMode_0_0value as Axis | undefined), (this._chainMode_0_1value as ChainStyle | undefined));
                    this._chainMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainModeAttribute((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | Resource | undefined));
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxLinesAttribute((undefined as int32 | Resource | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as double | string | Resource | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontSizeAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as double | string | Resource | undefined));
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontSizeAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._heightAdaptivePolicy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._heightAdaptivePolicy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHeightAdaptivePolicyAttribute((this._heightAdaptivePolicy_0_0value as TextHeightAdaptivePolicy | undefined));
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHeightAdaptivePolicyAttribute((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (this._enabled_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enabled_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnabledAttribute((this._enabled_0_0value as boolean | undefined));
                    this._enabled_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enabled_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enabled_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnabledAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SecurityComponentMethodModifier): void {
        this._state = modifier._state;
        if (modifier._iconSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iconSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iconSize(modifier._iconSize_0_0value);
                    break;
                }
                default: {
                    this.iconSize((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection((undefined as SecurityComponentLayoutDirection | undefined));
                }
            }
        }
        if (modifier._position_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._position_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.position(modifier._position_0_0value);
                    break;
                }
                default: {
                    this.position((undefined as Position | undefined));
                }
            }
        }
        if (modifier._markAnchor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._markAnchor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.markAnchor(modifier._markAnchor_0_0value);
                    break;
                }
                default: {
                    this.markAnchor((undefined as Position | undefined));
                }
            }
        }
        if (modifier._offset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._offset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.offset(modifier._offset_0_0value);
                    break;
                }
                default: {
                    this.offset((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | Resource | undefined));
                }
            }
        }
        if (modifier._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | Resource | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._iconColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iconColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iconColor(modifier._iconColor_0_0value);
                    break;
                }
                default: {
                    this.iconColor((undefined as ResourceColor | undefined));
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
        if (modifier._borderStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderStyle(modifier._borderStyle_0_0value);
                    break;
                }
                default: {
                    this.borderStyle((undefined as BorderStyle | undefined));
                }
            }
        }
        if (modifier._borderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderWidth(modifier._borderWidth_0_0value);
                    break;
                }
                default: {
                    this.borderWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._borderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderColor(modifier._borderColor_0_0value);
                    break;
                }
                default: {
                    this.borderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._borderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderRadius(modifier._borderRadius_0_0value);
                    break;
                }
                default: {
                    this.borderRadius((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (modifier._padding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._padding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.padding(modifier._padding_0_0value);
                    break;
                }
                default: {
                    this.padding((undefined as Padding | Dimension | undefined));
                }
            }
        }
        if (modifier._textIconSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textIconSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textIconSpace(modifier._textIconSpace_0_0value);
                    break;
                }
                default: {
                    this.textIconSpace((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (modifier._width_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._width_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.width(modifier._width_0_0value);
                    break;
                }
                default: {
                    this.width((undefined as Length | undefined));
                }
            }
        }
        if (modifier._height_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._height_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.height(modifier._height_0_0value);
                    break;
                }
                default: {
                    this.height((undefined as Length | undefined));
                }
            }
        }
        if (modifier._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as SizeOptions | undefined));
                }
            }
        }
        if (modifier._constraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._constraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.constraintSize(modifier._constraintSize_0_0value);
                    break;
                }
                default: {
                    this.constraintSize((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (modifier._align_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._align_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.align(modifier._align_0_0value);
                    break;
                }
                default: {
                    this.align((undefined as Alignment | undefined));
                }
            }
        }
        if (modifier._alignRules_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignRules_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignRules(modifier._alignRules_0_0value);
                    break;
                }
                default: {
                    this.alignRules((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (modifier._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
        if (modifier._chainMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainMode(modifier._chainMode_0_0value, modifier._chainMode_0_1value);
                    break;
                }
                default: {
                    this.chainMode((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | Resource | undefined));
                }
            }
        }
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._heightAdaptivePolicy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._heightAdaptivePolicy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.heightAdaptivePolicy(modifier._heightAdaptivePolicy_0_0value);
                    break;
                }
                default: {
                    this.heightAdaptivePolicy((undefined as TextHeightAdaptivePolicy | undefined));
                }
            }
        }
        if (modifier._enabled_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enabled_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._iconSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._iconSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._iconSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._iconSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        if (((this._layoutDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutDirection_0_0value = value
            this._state.fireChange()
        } else
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    position(value: Position | undefined): this {
        if (((this._position_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._position_0_flag = AttributeUpdaterFlag.UPDATE
            this._position_0_0value = value
            this._state.fireChange()
        } else
        {
            this._position_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    markAnchor(value: Position | undefined): this {
        if (((this._markAnchor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._markAnchor_0_flag = AttributeUpdaterFlag.UPDATE
            this._markAnchor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._markAnchor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._offset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._offset_0_flag = AttributeUpdaterFlag.UPDATE
            this._offset_0_0value = value
            this._state.fireChange()
        } else
        {
            this._offset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: Dimension | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | Resource | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    iconColor(value: ResourceColor | undefined): this {
        if (((this._iconColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._iconColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._iconColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._iconColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._backgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderStyle(value: BorderStyle | undefined): this {
        if (((this._borderStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._borderStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderWidth(value: Dimension | undefined): this {
        if (((this._borderWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._borderWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderColor(value: ResourceColor | undefined): this {
        if (((this._borderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._borderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        if (((this._borderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderRadius_0_0value = radius
            this._state.fireChange()
        } else
        {
            this._borderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    padding(value: Padding | Dimension | undefined): this {
        if (((this._padding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._padding_0_flag = AttributeUpdaterFlag.UPDATE
            this._padding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._padding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textIconSpace(value: Dimension | undefined): this {
        if (((this._textIconSpace_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textIconSpace_0_flag = AttributeUpdaterFlag.UPDATE
            this._textIconSpace_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textIconSpace_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._key_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._key_0_0value) !== (value)))
        {
            this._key_0_flag = AttributeUpdaterFlag.UPDATE
            this._key_0_0value = value
            this._state.fireChange()
        } else
        {
            this._key_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    width(value: Length | undefined): this {
        if (((this._width_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._width_0_flag = AttributeUpdaterFlag.UPDATE
            this._width_0_0value = value
            this._state.fireChange()
        } else
        {
            this._width_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    height(value: Length | undefined): this {
        if (((this._height_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._height_0_flag = AttributeUpdaterFlag.UPDATE
            this._height_0_0value = value
            this._state.fireChange()
        } else
        {
            this._height_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    size(value: SizeOptions | undefined): this {
        if (((this._size_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._size_0_flag = AttributeUpdaterFlag.UPDATE
            this._size_0_0value = value
            this._state.fireChange()
        } else
        {
            this._size_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (((this._constraintSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._constraintSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._constraintSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._constraintSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    align(alignType: Alignment | undefined): this {
        if (((this._align_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._align_0_flag = AttributeUpdaterFlag.UPDATE
            this._align_0_0value = alignType
            this._state.fireChange()
        } else
        {
            this._align_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alignRules(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        if (((this._alignRules_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignRules_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignRules_0_0value = alignRule
            this._state.fireChange()
        } else
        {
            this._alignRules_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    id(description: string | undefined): this {
        if (((this._id_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._id_0_0value) !== (description)))
        {
            this._id_0_flag = AttributeUpdaterFlag.UPDATE
            this._id_0_0value = description
            this._state.fireChange()
        } else
        {
            this._id_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (((this._chainMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._chainMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainMode_0_0value = direction
            this._chainMode_0_1value = style
            this._state.fireChange()
        } else
        {
            this._chainMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(scale: double | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = scale
            this._state.fireChange()
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(scale: double | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = scale
            this._state.fireChange()
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLines(line: int32 | Resource | undefined): this {
        if (((this._maxLines_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLines_0_0value = line
            this._state.fireChange()
        } else
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(minSize: double | string | Resource | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = minSize
            this._state.fireChange()
        } else
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontSize(maxSize: double | string | Resource | undefined): this {
        if (((this._maxFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontSize_0_0value = maxSize
            this._state.fireChange()
        } else
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        if (((this._heightAdaptivePolicy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.UPDATE
            this._heightAdaptivePolicy_0_0value = policy
            this._state.fireChange()
        } else
        {
            this._heightAdaptivePolicy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enabled(respond: boolean | undefined): this {
        if (((this._enabled_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enabled_0_0value) !== (respond)))
        {
            this._enabled_0_flag = AttributeUpdaterFlag.UPDATE
            this._enabled_0_0value = respond
            this._state.fireChange()
        } else
        {
            this._enabled_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
