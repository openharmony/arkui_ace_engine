/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "core/components/scroll/scroll_controller_base.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativeListScroller : public NativeNGScroller {
    DECL_TYPE(ListScroller, OHOS::FFI::FFIData)
public:
    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup);
    void ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);
    ListItemGroupIndex GetVisibleListContentInfo(double x, double y);
    void CloseAllSwipeActions();
    void CloseAllSwipeActionsWithCallback(const std::function<void()>& onFinishCallback);
};
}

extern "C" {
struct DividerParams {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

struct FfiOffsetRemain {
    double dxRemain;
    double dyRemain;
};

struct CJVisibleListContentInfo {
    int32_t index;
    int32_t itemGroupArea;
    int32_t itemIndexInGroup;
};

CJ_EXPORT void FfiOHOSAceFrameworkListCreate(double space, int32_t unit, int32_t initialIndex, int64_t scrollerID);
CJ_EXPORT void FfiOHOSAceFrameworkListSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetDirection(int32_t direction);
CJ_EXPORT void FfiOHOSAceFrameworkListSetDivider(DividerParams params);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEditMode(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEdgeEffect(int32_t edgeEffect);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEdgeEffectWithOption(int32_t edgeEffect, bool options);
CJ_EXPORT void FfiOHOSAceFrameworkListSetCachedCount(int32_t cachedCount);
CJ_EXPORT void FfiOHOSAceFrameworkListSetScrollBar(int32_t barState);
CJ_EXPORT void FfiOHOSAceFrameworkListScrollBarColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkListScrollBarWidth(double value, int32_t valueUnit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetChainAnimation(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetMultiSelectable(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanes(int32_t lanes);
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanesGutter(int32_t lanes, double gutter, int32_t gutterUnit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanesByLengthConstrain(
    double min, int32_t minUnit, double max, int32_t maxUnit);

struct LanesParams {
    double min;
    int32_t minUnit;
    double max;
    int32_t maxUnit;
    double gutter;
    int32_t gutterUnit;
};
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanesGutterByLengthConstrain(LanesParams lanesParams);
CJ_EXPORT void FfiOHOSAceFrameworkListSetAlignListItem(int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkListSetSticky(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkListSetNestedScroll(int32_t scrollForward, int32_t scrollBackward);
CJ_EXPORT void FfiOHOSAceFrameworkListSetFriction(double friction);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEnableScrollInteraction(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetContentStartOffset(double offset);
CJ_EXPORT void FfiOHOSAceFrameworkListSetContentEndOffset(double offset);
CJ_EXPORT void FfiOHOSAceFrameworkListSetScrollSnapAlign(int32_t scrollSnapAlign);
CJ_EXPORT void FfiOHOSAceFrameworkListSetMaintainPosition(bool enabled);
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkListSetItemDeleteCallback(bool (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkListSetScrollIndexCallback(void (*callback)(int32_t firstIndex, int32_t lastIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollIndexCallback(void (*callback)(int32_t firstIndex,
    int32_t lastIndex, int32_t centerIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollCallback(void (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnReachStartCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnReachEndCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollStartCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollStopCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollBeginCallback(FfiOffsetRemain (*callback)(double dx, double dy));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemMoveCallback(bool (*callback)(int32_t start, int32_t end));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollVisibleContentChange(void (*callback)(
    CJVisibleListContentInfo start, CJVisibleListContentInfo end));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemDragStartCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemDragEnterCallback(void (*callback)(CJPosition itemDragInfo));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemDragMoveCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex, int32_t insertIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemDragLeaveCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnItemDropCallback(void (*callback)(
    CJPosition itemDragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess));
CJ_EXPORT int64_t FfiOHOSAceFrameworkListScrollerCtor();
CJ_EXPORT CJRectResult FfiOHOSAceFrameworkListScrollerGetItemRectInGroup(
    int64_t selfId, int32_t index, int32_t indexInGroup);
CJ_EXPORT void FfiOHOSAceFrameworkListScrollerScrollToItemInGroup(
    int64_t selfId, int32_t index, int32_t indexInGroup, bool smooth, int32_t align);
CJ_EXPORT CJVisibleListContentInfo FfiOHOSAceFrameworkListScrollerGetVisibleListContentInfo(
    int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkListScrollerCloseAllSwipeActions(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkListScrollerCloseAllSwipeActionsWithCallback(int64_t selfId,
    void (*onFinishCallback)());
}

#endif // OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H
