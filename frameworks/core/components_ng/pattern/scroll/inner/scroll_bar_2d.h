/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_2D_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_2D_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d_painter.h"

namespace OHOS::Ace::NG {
class ScrollPattern;
struct ScrollBarProperty;

class ScrollBar2D final : public AceType {
    DECLARE_ACE_TYPE(ScrollBar2D, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(ScrollBar2D);

public:
    explicit ScrollBar2D(ScrollPattern& pattern);
    ~ScrollBar2D() final;

    const RefPtr<ScrollBar2DPainter>& GetPainter() const
    {
        return painter_;
    }
    const ScrollBar& GetVerticalBar() const
    {
        return vertical_;
    }
    const ScrollBar& GetHorizontalBar() const
    {
        return horizontal_;
    }
    void ResetAnimationSignals();

    void Update(const std::unique_ptr<ScrollBarProperty>& props);

    /**
     * @brief Synchronize layout states of the scroll bars from Scroll component.
     */
    void SyncLayout(const OffsetF& offset, const SizeF& viewSize, const SizeF& content);

private:
    void InitGestures(ScrollBar& bar, Axis axis);
    void RemoveGestures(ScrollBar& bar);

    ScrollPattern& pattern_;

    ScrollBar vertical_;
    ScrollBar horizontal_;
    RefPtr<ScrollBar2DPainter> painter_ = AceType::MakeRefPtr<ScrollBar2DPainter>();
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_2D_H
