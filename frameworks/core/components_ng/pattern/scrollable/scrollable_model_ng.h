/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
namespace OHOS::Ace::NG {

constexpr Dimension DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE = Dimension(32.0f, DimensionUnit::VP); // default value
class ACE_FORCE_EXPORT ScrollableModelNG {
public:
    static void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge = EffectEdge::ALL);

    static void SetScrollBarMode(DisplayMode value);
    static void SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& value);
    static void SetScrollBarColor(const std::string& value);
    static void SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetScrollBarWidth(const std::string& value);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& value);

    static void SetOnScroll(OnScrollEvent&& onScroll);
    static void SetOnWillScroll(OnWillScrollEvent&& onScroll);
    static void SetOnDidScroll(OnScrollEvent&& onScroll);
    static void SetOnScrollStart(OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(OnScrollStopEvent&& onScrollStop);
    static void SetOnReachStart(OnReachEvent&& onReachStart);
    static void SetOnReachEnd(OnReachEvent&& onReachEnd);
    static void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin);
    static void SetFadingEdge(
        bool fadingEdge, const Dimension& fadingEdgeLength = DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE);
    static void SetFadingEdge(FrameNode* frameNode, bool fadingEdge,
        const Dimension& fadingEdgeLength = DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE);
    static void SetContentClip(ContentClipMode mode, const RefPtr<ShapeRect>& rect);

    static void SetEdgeEffect(
        FrameNode* frameNode, EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge = EffectEdge::ALL);
    static void SetScrollBarMode(FrameNode* frameNode, int32_t displayNumber);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::string& value);
    static void SetScrollBarColor(FrameNode* frameNode, const std::string& value);
    static void SetMaxFlingSpeed(double max);
    static void SetOnWillScroll(FrameNode* frameNode, OnWillScrollEvent&& onScroll);
    static void SetOnDidScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);

    static int32_t GetEdgeEffect(FrameNode* frameNode);
    static int32_t GetAlwaysEnabled(FrameNode* frameNode);
    static void SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin);
    static void SetMaxFlingSpeed(FrameNode* frameNode, double max);
    /**
     * @return maximum fling speed, Unit: vp/s.
     */
    static float GetMaxFlingSpeed(FrameNode* frameNode);
    static void SetContentClip(FrameNode* frameNode, ContentClipMode mode, const RefPtr<ShapeRect>& rect);
    static ContentClipMode GetContentClip(FrameNode* frameNode);
    static void ResetContentClip(FrameNode* frameNode);
    static bool GetFadingEdge(FrameNode* frameNode);
    static float GetFadingEdgeLength(FrameNode* frameNode);

#ifdef SUPPORT_DIGITAL_CROWN
    static void SetDigitalCrownSensitivity(CrownSensitivity sensitivity);
#endif
    static void ResetScrollBarWidth(FrameNode* frameNode);
    static void ResetScrollBarColor(FrameNode* frameNode);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& friction);

    static void SetBackToTop(bool backToTop);
    static void SetBackToTop(FrameNode* frameNode, bool backToTop);
    static bool GetBackToTop(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_MODEL_H
