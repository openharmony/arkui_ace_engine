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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_PATTERN_H

#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_render_property.h"
#include "frameworks/core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class RefreshPattern : public Pattern {
    DECLARE_ACE_TYPE(RefreshPattern, Pattern);

public:
    RefreshPattern() = default;
    ~RefreshPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RefreshLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RefreshLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<RefreshRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RefreshEventHub>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }
    void OnModifyDone() override;
    void FireStateChange(int32_t value);
    void FireRefreshing();
    void FireChangeEvent(const std::string& value);

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnAttachToFrameNode() override;
    void UpdateScrollableOffset(float delta);
    float GetFriction(float percentage) const;
    float GetOffset(float delta) const;
    float MaxScrollableHeight() const;
    double GetLoadingDiameter() const;
    OffsetF GetLoadingOffset() const;
    OffsetF GetShowTimeOffset() const;
    float GetOpacity() const;
    RefreshStatus GetNextStatus();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart();
    void HandleDragUpdate(float delta);
    void HandleDragEnd();
    void HandleDragCancel();
    static std::string GetFormatDateTime();
    void OnActive() override {}
    void OnInActive() override;
    RefPtr<PanEvent> panEvent_;
    OffsetF timeOffset_;

    RefPtr<FrameNode> textChild_;
    RefPtr<FrameNode> progressChild_;
    ACE_DISALLOW_COPY_AND_MOVE(RefreshPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
