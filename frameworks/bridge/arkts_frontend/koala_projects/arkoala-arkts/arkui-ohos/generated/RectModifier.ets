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

import { CommonMethod, CommonShapeMethod } from "./component/common"
import { ResourceColor, Length } from "./component/units"
import { Color, LineCapStyle, LineJoinStyle } from "./component/enums"
import { Resource } from "global.resource"
import { CommonShapeMethodModifier } from "./CommonShapeMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkRectPeer, RadiusItem, RectAttribute } from "./component/rect"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
export class RectModifier extends CommonMethodModifier implements RectAttribute,AttributeModifier<RectAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RectAttribute): void { }
    applyPressedAttribute(instance: RectAttribute): void { }
    applyFocusedAttribute(instance: RectAttribute): void { }
    applyDisabledAttribute(instance: RectAttribute): void { }
    applySelectedAttribute(instance: RectAttribute): void { }
    _radiusWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radiusWidth_0_0value?: double | string | undefined
    _radiusHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radiusHeight_0_0value?: double | string | undefined
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: Length | Array<RadiusItem> | undefined
    _stroke_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stroke_0_0value?: ResourceColor | undefined
    _fill_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fill_0_0value?: ResourceColor | undefined
    _strokeDashOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashOffset_0_0value?: number | string | undefined
    _strokeLineCap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineCap_0_0value?: LineCapStyle | undefined
    _strokeLineJoin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineJoin_0_0value?: LineJoinStyle | undefined
    _strokeMiterLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeMiterLimit_0_0value?: number | string | undefined
    _strokeOpacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeOpacity_0_0value?: number | string | Resource | undefined
    _fillOpacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillOpacity_0_0value?: number | string | Resource | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: Length | undefined
    _antiAlias_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _antiAlias_0_0value?: boolean | undefined
    _strokeDashArray_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashArray_0_0value?: Array<Length> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRectPeer;
        if (this._radiusWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radiusWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusWidthAttribute((this._radiusWidth_0_0value as double | string | undefined));
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._radiusHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radiusHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusHeightAttribute((this._radiusHeight_0_0value as double | string | undefined));
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusHeightAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusAttribute((this._radius_0_0value as Length | Array<RadiusItem> | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusAttribute((undefined as Length | Array<RadiusItem> | undefined));
                }
            }
        }
        if (this._stroke_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stroke_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeAttribute((this._stroke_0_0value as ResourceColor | undefined));
                    this._stroke_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stroke_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stroke_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fill_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillAttribute((this._fill_0_0value as ResourceColor | undefined));
                    this._fill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fill_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._strokeDashOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeDashOffsetAttribute((this._strokeDashOffset_0_0value as number | string | undefined));
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeDashOffsetAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._strokeLineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeLineCapAttribute((this._strokeLineCap_0_0value as LineCapStyle | undefined));
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeLineCapAttribute((undefined as LineCapStyle | undefined));
                }
            }
        }
        if (this._strokeLineJoin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineJoin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeLineJoinAttribute((this._strokeLineJoin_0_0value as LineJoinStyle | undefined));
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeLineJoinAttribute((undefined as LineJoinStyle | undefined));
                }
            }
        }
        if (this._strokeMiterLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeMiterLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeMiterLimitAttribute((this._strokeMiterLimit_0_0value as number | string | undefined));
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeMiterLimitAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._strokeOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeOpacityAttribute((this._strokeOpacity_0_0value as number | string | Resource | undefined));
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeOpacityAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._fillOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillOpacityAttribute((this._fillOpacity_0_0value as number | string | Resource | undefined));
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillOpacityAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._antiAlias_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._antiAlias_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAntiAliasAttribute((this._antiAlias_0_0value as boolean | undefined));
                    this._antiAlias_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._antiAlias_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._antiAlias_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAntiAliasAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._strokeDashArray_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashArray_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeDashArrayAttribute((this._strokeDashArray_0_0value as Array<Length> | undefined));
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeDashArrayAttribute((undefined as Array<Length> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RectModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._radiusWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radiusWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radiusWidth(modifier._radiusWidth_0_0value);
                    break;
                }
                default: {
                    this.radiusWidth((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._radiusHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radiusHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radiusHeight(modifier._radiusHeight_0_0value);
                    break;
                }
                default: {
                    this.radiusHeight((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radius(modifier._radius_0_0value);
                    break;
                }
                default: {
                    this.radius((undefined as Length | Array<RadiusItem> | undefined));
                }
            }
        }
        if (modifier._stroke_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stroke_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stroke(modifier._stroke_0_0value);
                    break;
                }
                default: {
                    this.stroke((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._fill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fill_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fill(modifier._fill_0_0value);
                    break;
                }
                default: {
                    this.fill((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._strokeDashOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashOffset(modifier._strokeDashOffset_0_0value);
                    break;
                }
                default: {
                    this.strokeDashOffset((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._strokeLineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineCap(modifier._strokeLineCap_0_0value);
                    break;
                }
                default: {
                    this.strokeLineCap((undefined as LineCapStyle | undefined));
                }
            }
        }
        if (modifier._strokeLineJoin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineJoin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineJoin(modifier._strokeLineJoin_0_0value);
                    break;
                }
                default: {
                    this.strokeLineJoin((undefined as LineJoinStyle | undefined));
                }
            }
        }
        if (modifier._strokeMiterLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeMiterLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeMiterLimit(modifier._strokeMiterLimit_0_0value);
                    break;
                }
                default: {
                    this.strokeMiterLimit((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._strokeOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeOpacity(modifier._strokeOpacity_0_0value);
                    break;
                }
                default: {
                    this.strokeOpacity((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._fillOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillOpacity(modifier._fillOpacity_0_0value);
                    break;
                }
                default: {
                    this.fillOpacity((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._antiAlias_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._antiAlias_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.antiAlias(modifier._antiAlias_0_0value);
                    break;
                }
                default: {
                    this.antiAlias((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._strokeDashArray_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashArray_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashArray(modifier._strokeDashArray_0_0value);
                    break;
                }
                default: {
                    this.strokeDashArray((undefined as Array<Length> | undefined));
                }
            }
        }
    }
    radiusWidth(value: double | string | undefined): this {
        if (((this._radiusWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radiusWidth_0_0value) !== (value)))
        {
            this._radiusWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._radiusWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._radiusWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radiusHeight(value: double | string | undefined): this {
        if (((this._radiusHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radiusHeight_0_0value) !== (value)))
        {
            this._radiusHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._radiusHeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._radiusHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radius(value: Length | Array<RadiusItem> | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
            this._state.fireChange()
        } else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stroke(value: ResourceColor | undefined): this {
        if (((this._stroke_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stroke_0_flag = AttributeUpdaterFlag.UPDATE
            this._stroke_0_0value = value
            this._state.fireChange()
        } else
        {
            this._stroke_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fill(value: ResourceColor | undefined): this {
        if (((this._fill_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fill_0_flag = AttributeUpdaterFlag.UPDATE
            this._fill_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fill_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashOffset(value: number | string | undefined): this {
        if (((this._strokeDashOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeDashOffset_0_0value) !== (value)))
        {
            this._strokeDashOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashOffset_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeDashOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        if (((this._strokeLineCap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeLineCap_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineCap_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeLineCap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (((this._strokeLineJoin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeLineJoin_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineJoin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeLineJoin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeMiterLimit(value: number | string | undefined): this {
        if (((this._strokeMiterLimit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeMiterLimit_0_0value) !== (value)))
        {
            this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeMiterLimit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeOpacity(value: number | string | Resource | undefined): this {
        if (((this._strokeOpacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeOpacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeOpacity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeOpacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillOpacity(value: number | string | Resource | undefined): this {
        if (((this._fillOpacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillOpacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillOpacity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fillOpacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    antiAlias(value: boolean | undefined): this {
        if (((this._antiAlias_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._antiAlias_0_0value) !== (value)))
        {
            this._antiAlias_0_flag = AttributeUpdaterFlag.UPDATE
            this._antiAlias_0_0value = value
            this._state.fireChange()
        } else
        {
            this._antiAlias_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        if (((this._strokeDashArray_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeDashArray_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashArray_0_0value = value
            this._state.fireChange()
        } else
        {
            this._strokeDashArray_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
