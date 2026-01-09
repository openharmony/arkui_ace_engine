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

import { CommonMethod, NestedScrollOptions, OnWillStopDraggingCallback, OnDidStopDraggingCallback, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback } from "./component/common"
import { BarState, Color, CrownSensitivity, EdgeEffect, FlexDirection, ScrollSource } from "./component/enums"
import { Resource } from "global.resource"
import { extractors, AttributeModifier } from "#handwritten"
import { RectShape } from "@ohos.arkui.shape"
import { ScrollableCommonMethodModifier } from "./ScrollableCommonMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkWaterFlowPeer, WaterFlowAttribute } from "./component/waterFlow"
import { int32 } from "@koalaui/common"
import { VoidCallback, ItemFillPolicy, ConstraintSizeOptions, Length, ScrollBarMargin } from "./component/units"
import { OnScrollFrameBeginCallback } from "./component/scroll"
import { ScrollState } from "./component/list"
export class WaterFlowModifier extends CommonMethodModifier implements WaterFlowAttribute,AttributeModifier<WaterFlowAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
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
    _columnsTemplate_0_0value?: string | ItemFillPolicy | undefined
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
    _cachedCount_0_0value?: int32 | undefined
    _syncLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _syncLoad_0_0value?: boolean | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((first: int32,last: int32) => void) | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: int32 | undefined
    _cachedCount_1_1value?: boolean | undefined
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBar_0_0value?: BarState | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: Color | int32 | string | Resource | undefined
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarWidth_0_0value?: double | string | undefined
    _scrollBarMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarMargin_0_0value?: ScrollBarMargin | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | undefined
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableScrollInteraction_0_0value?: boolean | undefined
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _friction_0_0value?: double | Resource | undefined
    _contentStartOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentStartOffset_0_0value?: double | Resource | undefined
    _contentEndOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentEndOffset_0_0value?: double | Resource | undefined
    _onWillStartDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStartDragging_0_0value?: VoidCallback | undefined
    _onWillStopDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStopDragging_0_0value?: OnWillStopDraggingCallback | undefined
    _onDidStopDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidStopDragging_0_0value?: OnDidStopDraggingCallback | undefined
    _onWillStartFling_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStartFling_0_0value?: VoidCallback | undefined
    _onDidStopFling_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidStopFling_0_0value?: VoidCallback | undefined
    _onReachStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachStart_0_0value?: (() => void) | undefined
    _onReachEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachEnd_0_0value?: (() => void) | undefined
    _onScrollStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStart_0_0value?: (() => void) | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: (() => void) | undefined
    _flingSpeedLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flingSpeedLimit_0_0value?: double | undefined
    _clipContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _backToTop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backToTop_0_0value?: boolean | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkWaterFlowPeer;
        if (this._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsTemplateAttribute((this._columnsTemplate_0_0value as string | ItemFillPolicy | undefined));
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsTemplateAttribute((undefined as string | ItemFillPolicy | undefined));
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
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as int32 | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSyncLoadAttribute((this._syncLoad_0_0value as boolean | undefined));
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSyncLoadAttribute((undefined as boolean | undefined));
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
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((first: int32,last: int32) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((first: int32,last: int32) => void) | undefined));
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
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as int32 | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarAttribute((this._scrollBar_0_0value as BarState | undefined));
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as Color | int32 | string | Resource | undefined));
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarColorAttribute((undefined as Color | int32 | string | Resource | undefined));
                }
            }
        }
        if (this._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as double | string | undefined));
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._scrollBarMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarMarginAttribute((this._scrollBarMargin_0_0value as ScrollBarMargin | undefined));
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarMarginAttribute((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (this._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableScrollInteractionAttribute((this._enableScrollInteraction_0_0value as boolean | undefined));
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableScrollInteractionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFrictionAttribute((this._friction_0_0value as double | Resource | undefined));
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._friction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFrictionAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentStartOffsetAttribute((this._contentStartOffset_0_0value as double | Resource | undefined));
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentStartOffsetAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentEndOffsetAttribute((this._contentEndOffset_0_0value as double | Resource | undefined));
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentEndOffsetAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._onWillStartDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStartDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStartDraggingAttribute((this._onWillStartDragging_0_0value as VoidCallback | undefined));
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStartDraggingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onWillStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStopDraggingAttribute((this._onWillStopDragging_0_0value as OnWillStopDraggingCallback | undefined));
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStopDraggingAttribute((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (this._onDidStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidStopDraggingAttribute((this._onDidStopDragging_0_0value as OnDidStopDraggingCallback | undefined));
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidStopDraggingAttribute((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (this._onWillStartFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStartFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStartFlingAttribute((this._onWillStartFling_0_0value as VoidCallback | undefined));
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStartFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDidStopFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidStopFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidStopFlingAttribute((this._onDidStopFling_0_0value as VoidCallback | undefined));
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidStopFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachStartAttribute((this._onReachStart_0_0value as (() => void) | undefined));
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachEndAttribute((this._onReachEnd_0_0value as (() => void) | undefined));
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachEndAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as (() => void) | undefined));
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as (() => void) | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as double | undefined));
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlingSpeedLimitAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClipContentAttribute((this._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClipContentAttribute((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackToTopAttribute((this._backToTop_0_0value as boolean | undefined));
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions | undefined | undefined));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (this._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined), (this._fadingEdge_0_1value as FadingEdgeOptions | undefined | undefined));
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WaterFlowModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate((undefined as string | ItemFillPolicy | undefined));
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
                    this.cachedCount((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.syncLoad(modifier._syncLoad_0_0value);
                    break;
                }
                default: {
                    this.syncLoad((undefined as boolean | undefined));
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
                    this.onScrollIndex((undefined as ((first: int32,last: int32) => void) | undefined));
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
                    this.cachedCount((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBar(modifier._scrollBar_0_0value);
                    break;
                }
                default: {
                    this.scrollBar((undefined as BarState | undefined));
                }
            }
        }
        if (modifier._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as Color | int32 | string | Resource | undefined));
                }
            }
        }
        if (modifier._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarWidth(modifier._scrollBarWidth_0_0value);
                    break;
                }
                default: {
                    this.scrollBarWidth((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._scrollBarMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarMargin(modifier._scrollBarMargin_0_0value);
                    break;
                }
                default: {
                    this.scrollBarMargin((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (modifier._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableScrollInteraction(modifier._enableScrollInteraction_0_0value);
                    break;
                }
                default: {
                    this.enableScrollInteraction((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.friction(modifier._friction_0_0value);
                    break;
                }
                default: {
                    this.friction((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentStartOffset(modifier._contentStartOffset_0_0value);
                    break;
                }
                default: {
                    this.contentStartOffset((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentEndOffset(modifier._contentEndOffset_0_0value);
                    break;
                }
                default: {
                    this.contentEndOffset((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._onWillStartDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStartDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStartDragging(modifier._onWillStartDragging_0_0value);
                    break;
                }
                default: {
                    this.onWillStartDragging((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onWillStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStopDragging(modifier._onWillStopDragging_0_0value);
                    break;
                }
                default: {
                    this.onWillStopDragging((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (modifier._onDidStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidStopDragging(modifier._onDidStopDragging_0_0value);
                    break;
                }
                default: {
                    this.onDidStopDragging((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (modifier._onWillStartFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStartFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStartFling(modifier._onWillStartFling_0_0value);
                    break;
                }
                default: {
                    this.onWillStartFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDidStopFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidStopFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidStopFling(modifier._onDidStopFling_0_0value);
                    break;
                }
                default: {
                    this.onDidStopFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachStart(modifier._onReachStart_0_0value);
                    break;
                }
                default: {
                    this.onReachStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachEnd(modifier._onReachEnd_0_0value);
                    break;
                }
                default: {
                    this.onReachEnd((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStart(modifier._onScrollStart_0_0value);
                    break;
                }
                default: {
                    this.onScrollStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flingSpeedLimit(modifier._flingSpeedLimit_0_0value);
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as double | undefined));
                }
            }
        }
        if (modifier._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clipContent(modifier._clipContent_0_0value);
                    break;
                }
                default: {
                    this.clipContent((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backToTop(modifier._backToTop_0_0value);
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value, modifier._edgeEffect_0_1value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (modifier._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fadingEdge(modifier._fadingEdge_0_0value, modifier._fadingEdge_0_1value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        if (((this._columnsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnsTemplate_0_0value) !== (value)))
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsTemplate_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: int32 | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
            this._state.fireChange()
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    syncLoad(value: boolean | undefined): this {
        if (((this._syncLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._syncLoad_0_0value) !== (value)))
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._syncLoad_0_0value = value
        } else
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._onScrollFrameBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollFrameBegin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        if (((this._onScrollIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollIndex_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (show)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = show
            this._state.fireChange()
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBar(value: BarState | undefined): this {
        if (((this._scrollBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBar_0_0value = value
            this._state.fireChange()
        } else
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarColor(value: Color | int32 | string | Resource | undefined): this {
        if (((this._scrollBarColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        if (((this._scrollBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollBarWidth_0_0value) !== (value)))
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarMargin(value: ScrollBarMargin | undefined): this {
        if (((this._scrollBarMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollBarMargin_0_0value) !== (value)))
        {
            this._scrollBarMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarMargin_0_0value = value
        } else
        {
            this._scrollBarMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (((this._enableScrollInteraction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableScrollInteraction_0_0value) !== (value)))
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableScrollInteraction_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    friction(value: double | Resource | undefined): this {
        if (((this._friction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._friction_0_flag = AttributeUpdaterFlag.UPDATE
            this._friction_0_0value = value
            this._state.fireChange()
        } else
        {
            this._friction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentStartOffset(value: double | Resource | undefined): this {
        if (((this._contentStartOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentStartOffset_0_0value = value
        } else
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentEndOffset(value: double | Resource | undefined): this {
        if (((this._contentEndOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentEndOffset_0_0value = value
        } else
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStartDragging(value: VoidCallback | undefined): this {
        if (((this._onWillStartDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStartDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStartDragging_0_0value = value
        } else
        {
            this._onWillStartDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStopDragging(value: OnWillStopDraggingCallback | undefined): this {
        if (((this._onWillStopDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStopDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStopDragging_0_0value = value
        } else
        {
            this._onWillStopDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidStopDragging(value: OnDidStopDraggingCallback | undefined): this {
        if (((this._onDidStopDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidStopDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidStopDragging_0_0value = value
        } else
        {
            this._onDidStopDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStartFling(value: VoidCallback | undefined): this {
        if (((this._onWillStartFling_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStartFling_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStartFling_0_0value = value
        } else
        {
            this._onWillStartFling_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidStopFling(value: VoidCallback | undefined): this {
        if (((this._onDidStopFling_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidStopFling_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidStopFling_0_0value = value
        } else
        {
            this._onDidStopFling_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        if (((this._onReachStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        if (((this._onReachEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        if (((this._onScrollStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        if (((this._onScrollStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        if (((this._flingSpeedLimit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flingSpeedLimit_0_0value) !== (value)))
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.UPDATE
            this._flingSpeedLimit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (((this._clipContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._clipContent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._backToTop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._backToTop_0_0value) !== (value)))
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.UPDATE
            this._backToTop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = edgeEffect
            this._edgeEffect_0_1value = options
            this._state.fireChange()
        } else
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (((this._fadingEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fadingEdge_0_0value) !== (enabled)) || (true))
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._fadingEdge_0_0value = enabled
            this._fadingEdge_0_1value = options
            this._state.fireChange()
        } else
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
