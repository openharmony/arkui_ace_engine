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

import { ScrollableCommonMethodModifier } from "./ScrollableCommonMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkWaterFlowPeer, WaterFlowAttribute } from "./component/waterFlow"
import { int32 } from "@koalaui/common"
import { ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback, CommonMethod } from "./component/common"
import { ConstraintSizeOptions, Length } from "./component/units"
import { Resource } from "global.resource"
import { FlexDirection, ScrollSource } from "./component/enums"
import { OnScrollFrameBeginCallback } from "./component/scroll"
import { ScrollState } from "./component/list"
export class WaterFlowModifier extends ScrollableCommonMethodModifier implements WaterFlowAttribute,AttributeModifier<WaterFlowAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WaterFlowAttribute): void { }
    applyPressedAttribute(instance: WaterFlowAttribute): void { }
    applyFocusedAttribute(instance: WaterFlowAttribute): void { }
    applyDisabledAttribute(instance: WaterFlowAttribute): void { }
    applySelectedAttribute(instance: WaterFlowAttribute): void { }
    _columnsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsTemplate_0_0value?: string | undefined
    _itemConstraintSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemConstraintSize_0_0value?: ConstraintSizeOptions | undefined
    _rowsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsTemplate_0_0value?: string | undefined
    _columnsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsGap_0_0value?: Length | undefined
    _rowsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsGap_0_0value?: Length | undefined
    _layoutDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutDirection_0_0value?: FlexDirection | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: number | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((first: number,last: number) => void) | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: number | undefined
    _cachedCount_1_1value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkWaterFlowPeer;
        if (this._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsTemplateAttribute((this._columnsTemplate_0_0value as string | undefined));
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._itemConstraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._itemConstraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setItemConstraintSizeAttribute((this._itemConstraintSize_0_0value as ConstraintSizeOptions | undefined));
                    this._itemConstraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemConstraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemConstraintSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setItemConstraintSizeAttribute((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (this._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsTemplateAttribute((this._rowsTemplate_0_0value as string | undefined));
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsGapAttribute((this._columnsGap_0_0value as Length | undefined));
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsGapAttribute((this._rowsGap_0_0value as Length | undefined));
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as FlexDirection | undefined));
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutDirectionAttribute((undefined as FlexDirection | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as number | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((first: number,last: number) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((first: number,last: number) => void) | undefined));
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as OnWillScrollCallback | undefined));
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillScrollAttribute((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as OnScrollCallback | undefined));
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidScrollAttribute((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as number | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WaterFlowModifier): void {
        super.mergeModifier(modifier)
        if (modifier._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._itemConstraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._itemConstraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemConstraintSize(modifier._itemConstraintSize_0_0value);
                    break;
                }
                default: {
                    this.itemConstraintSize((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (modifier._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsTemplate(modifier._rowsTemplate_0_0value);
                    break;
                }
                default: {
                    this.rowsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap((undefined as Length | undefined));
                }
            }
        }
        if (modifier._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap((undefined as Length | undefined));
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
                    this.layoutDirection((undefined as FlexDirection | undefined));
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (modifier._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollIndex(modifier._onScrollIndex_0_0value);
                    break;
                }
                default: {
                    this.onScrollIndex((undefined as ((first: number,last: number) => void) | undefined));
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    columnsTemplate(value: string | undefined): this {
        if (((this._columnsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnsTemplate_0_0value) !== (value)))
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsTemplate_0_0value = value
        } else
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        if (((this._itemConstraintSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._itemConstraintSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemConstraintSize_0_0value = value
        } else
        {
            this._itemConstraintSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsTemplate(value: string | undefined): this {
        if (((this._rowsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._rowsTemplate_0_0value) !== (value)))
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsTemplate_0_0value = value
        } else
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnsGap(value: Length | undefined): this {
        if (((this._columnsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsGap_0_0value = value
        } else
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsGap(value: Length | undefined): this {
        if (((this._rowsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsGap_0_0value = value
        } else
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutDirection(value: FlexDirection | undefined): this {
        if (((this._layoutDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutDirection_0_0value = value
        } else
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: number | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._onScrollFrameBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollFrameBegin_0_0value = value
        } else
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (((this._onScrollIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollIndex_0_0value = value
        } else
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (((this._onWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillScroll_0_0value = value
        } else
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        if (((this._onDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidScroll_0_0value = value
        } else
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (show)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = show
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
