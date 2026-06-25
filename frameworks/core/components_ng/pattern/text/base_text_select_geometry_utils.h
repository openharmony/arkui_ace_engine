/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_BASE_TEXT_SELECT_GEOMETRY_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_BASE_TEXT_SELECT_GEOMETRY_UTILS_H

#include <optional>
#include <utility>
#include <vector>

#include "base/geometry/offset.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {

// Static geometry utility class shared by BaseTextSelectOverlay, TextSelectionChild, etc.
class BaseTextSelectGeometryUtils {
public:
    // Get the content rect of a frame node (considering scrollable clip, geometry content, etc.)
    static bool GetFrameNodeContentRect(const RefPtr<FrameNode>& node, RectF& contentRect);

    // Get scrollable paint property based clip content rect.
    static bool GetScrollableClipContentRect(const RefPtr<FrameNode>& node, RectF& rect);

    static std::pair<ContentClipMode, std::optional<ContentClip>> GetScrollableClipInfo(
        const RefPtr<FrameNode>& node);

    static bool CheckUnsupportedTransformMatrix(const RefPtr<RenderContext>& context, bool checkScale);

    // Same semantics as BaseTextSelectOverlay::HasUnsupportedTransform before extraction.
    static bool HasUnsupportedTransform(const RefPtr<FrameNode>& host, bool checkScale);
    static bool HasTransformAttr(const RefPtr<FrameNode>& host);
    static bool GetRenderClipValue(const RefPtr<FrameNode>& host, bool defaultClip);
    static RectF GetVisibleRect(const RefPtr<FrameNode>& node, const RectF& visibleRect);
    static RectF MergeSelectedBoxes(
        const std::vector<RectF>& boxes, const RectF& contentRect, const RectF& textRect, const OffsetF& paintOffset);
    static void GetGlobalPointsWithTransform(
        const RefPtr<FrameNode>& host, bool hasTransform, std::vector<OffsetF>& points);
    static void GetGlobalRectWithTransform(const RefPtr<FrameNode>& host, bool hasTransform, RectF& localRect);
    static std::vector<OffsetF> GetGlobalRectVertexWithTransform(
        const RefPtr<FrameNode>& host, bool hasTransform, const RectF& rect, float extendValue = 0.0f);
    static bool CalculateClippedRect(const RefPtr<FrameNode>& host, RectF& contentRect);
    static void UpdateClipHandleViewPort(const RefPtr<FrameNode>& host, bool renderClipValue, RectF& rect);

private:
    static bool CheckHasTransformMatrix(const RefPtr<RenderContext>& context);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_BASE_TEXT_SELECT_GEOMETRY_UTILS_H
