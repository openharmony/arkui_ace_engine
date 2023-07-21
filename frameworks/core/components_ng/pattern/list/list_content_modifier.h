/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
struct DividerInfo {
    float constrainStrokeWidth;
    float crossSize;
    float startMargin;
    float endMargin;
    float space;
    float mainPadding;
    float crossPadding;
    bool isVertical;
    int32_t lanes;
    int32_t totalItemCount;
    Color color;
    float laneGutter = 0.0f;
};

class ListContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ListContentModifier, ContentModifier);
public:
    using PositionMap = ListLayoutAlgorithm::PositionMap;
    ListContentModifier(const OffsetF& clipOffset, const SizeF& clipSize);
    ~ListContentModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetClipOffset(OffsetF offset)
    {
        clipOffset_->Set(offset);
    }

    void SetClipSize(SizeF size)
    {
        clipSize_->Set(size);
    }

    void SetClip(bool clip)
    {
        clip_->Set(clip);
    }

    void SetDividerInfo(DividerInfo&& dividerInfo)
    {
        dividerInfo_ = dividerInfo;
    }

    void ResetDividerInfo()
    {
        if (dividerInfo_.has_value()) {
            dividerInfo_.reset();
            FlushDivider();
        }
    }

    void SetItemsPosition(const PositionMap& positionMap)
    {
        itemPosition_ = positionMap;
    }

    static void PaintDivider(const DividerInfo& dividerInfo, const PositionMap& itemPosition, RSCanvas& canvas);

    void FlushDivider()
    {
        flushDivider_->Set(!flushDivider_->Get());
    }

private:
    RefPtr<AnimatablePropertyOffsetF> clipOffset_;
    RefPtr<AnimatablePropertySizeF> clipSize_;
    RefPtr<PropertyBool> clip_;

    std::optional<DividerInfo> dividerInfo_;
    PositionMap itemPosition_;
    RefPtr<PropertyBool> flushDivider_;

    ACE_DISALLOW_COPY_AND_MOVE(ListContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CONTENT_MODIFIER_H
