/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PATTERN_H

#include "gmock/gmock.h"

#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class MockPattern : public Pattern {
    DECLARE_ACE_TYPE(MockPattern, Pattern);

public:
    MockPattern() = default;
    ~MockPattern() override = default;

    MOCK_CONST_METHOD0(IsAtomicNode, bool());
    MOCK_CONST_METHOD0(GetContextParam, std::optional<RenderContext::ContextParam>());
    MOCK_CONST_METHOD0(GetOverridePaintRect, std::optional<RectF>());
    MOCK_METHOD0(CreateAccessibilityProperty, RefPtr<AccessibilityProperty>());
    MOCK_METHOD0(CreatePaintProperty, RefPtr<PaintProperty>());
    MOCK_METHOD0(CreateLayoutProperty, RefPtr<LayoutProperty>());
    MOCK_METHOD0(CreateLayoutAlgorithm, RefPtr<LayoutAlgorithm>());
    MOCK_METHOD0(CreateNodePaintMethod, RefPtr<NodePaintMethod>());
    MOCK_METHOD0(CreateEventHub, RefPtr<EventHub>());
    MOCK_METHOD0(OnContextAttached, void());
    MOCK_METHOD0(OnModifyDone, void());
    MOCK_METHOD0(OnMountToParentDone, void());
    MOCK_CONST_METHOD0(IsRootPattern, bool());
    MOCK_CONST_METHOD0(IsMeasureBoundary, bool());
    MOCK_CONST_METHOD0(IsRenderBoundary, bool());
    MOCK_METHOD3(OnDirtyLayoutWrapperSwap, bool(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout));
    MOCK_METHOD2(
        OnDirtyLayoutWrapperSwap, bool(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig));
    MOCK_METHOD0(DumpInfo, void());
    MOCK_METHOD0(OnRebuildFrame, void());
    MOCK_METHOD0(BeforeCreateLayoutWrapper, void());
    MOCK_METHOD0(BeforeCreatePaintWrapper, void());
    MOCK_METHOD0(GetScopeFocusAlgorithm, ScopeFocusAlgorithm());
    MOCK_METHOD0(OnInActive, void());
    MOCK_METHOD0(OnActive, void());
    MOCK_METHOD0(OnWindowShow, void());
    MOCK_METHOD0(OnWindowHide, void());
    MOCK_METHOD0(OnWindowFocused, void());
    MOCK_METHOD0(OnWindowUnfocused, void());
    MOCK_METHOD1(OnNotifyMemoryLevel, void(int32_t level));
    MOCK_METHOD0(OnAttachToFrameNode, void());
    MOCK_METHOD1(OnDetachFromFrameNode, void(FrameNode* frameNode));
    MOCK_CONST_METHOD2(ToJsonValue, void(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter));
    MOCK_METHOD0(ProvideRestoreInfo, std::string());
    MOCK_METHOD0(OnAreaChangedInner, void());
    MOCK_METHOD3(OnWindowSizeChanged, void(int32_t width, int32_t height, WindowSizeChangeReason type));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PATTERN_H
