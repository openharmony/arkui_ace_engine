/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_MODEL_STATIC_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT ScrollableModelStatic {
public:
    static void SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& value);
    static void SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetNestedScroll(FrameNode* frameNode,
        const std::optional<NestedScrollMode>& forward, const std::optional<NestedScrollMode>& backward);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& friction);
    static void SetMaxFlingSpeed(FrameNode* frameNode,  const std::optional<double>& max);
    static void SetContentClip(FrameNode* frameNode, ContentClipMode mode, const RefPtr<ShapeRect>& rect);
    static void SetBackToTop(FrameNode* frameNode, bool backToTop);
    static void SetEdgeEffect(
        FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect, const std::optional<bool>& alwaysEnabled,
        EffectEdge effectEdge = EffectEdge::ALL);
    static void SetFadingEdge(FrameNode* frameNode, const std::optional<bool>& fadingEdge,
            const std::optional<Dimension>& fadingEdgeLength);

    static void SetOnWillScroll(FrameNode* frameNode, OnWillScrollEvent&& onScroll);
    static void SetOnDidScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);

#ifdef SUPPORT_DIGITAL_CROWN
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, const std::optional<CrownSensitivity>& sensitivity);
#endif
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_STATIC_H
