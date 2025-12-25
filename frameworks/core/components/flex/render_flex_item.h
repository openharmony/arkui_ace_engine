/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_RENDER_FLEX_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_RENDER_FLEX_ITEM_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/proxy/render_proxy.h"

namespace OHOS::Ace {

class ACE_EXPORT RenderFlexItem final : public RenderProxy {
    DECLARE_ACE_TYPE(RenderFlexItem, RenderProxy);

public:
    static RefPtr<RenderNode> Create();

    void OnAttachContext() override
    {
        positionParam_.left.first.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderFlexItem = weak.Upgrade();
            if (renderFlexItem) {
                renderFlexItem->MarkNeedLayout();
            }
        });
        positionParam_.right.first.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderFlexItem = weak.Upgrade();
            if (renderFlexItem) {
                renderFlexItem->MarkNeedLayout();
            }
        });
        positionParam_.top.first.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderFlexItem = weak.Upgrade();
            if (renderFlexItem) {
                renderFlexItem->MarkNeedLayout();
            }
        });
        positionParam_.bottom.first.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
            auto renderFlexItem = weak.Upgrade();
            if (renderFlexItem) {
                renderFlexItem->MarkNeedLayout();
            }
        });
    }

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    double GetFlexGrow() const
    {
        return flexGrow_;
    }

    void SetFlexGrow(double flexGrow)
    {
        flexGrow_ = flexGrow;
    }

    double GetFlexShrink() const
    {
        return flexShrink_;
    }

    void SetFlexShrink(double flexShrink)
    {
        flexShrink_ = flexShrink;
    }

    // should not used in Update.
    double GetFlexBasisToPx() const
    {
        auto basis = NormalizeToPx(flexBasis_);
        return basis;
    }

    // should not used in Update.
    const Dimension& GetFlexBasis() const
    {
        return flexBasis_;
    }

    void SetFlexBasis(const Dimension& flexBasis)
    {
        flexBasis_ = flexBasis;
    }

    void SetFlexBasis(double flexBasis)
    {
        flexBasis_ = Dimension(flexBasis);
    }

    bool GetStretchFlag() const
    {
        return canStretch_;
    }

    FlexAlign GetAlignSelf() const
    {
        return alignSelf_;
    }

    void SetAlignSelf(FlexAlign alignSelf)
    {
        alignSelf_ = alignSelf;
    }

    LayoutParam GetNormalizedConstraints() const
    {
        Size min = Size(NormalizePercentToPx(minWidth_, false), NormalizePercentToPx(minHeight_, true));
        Size max = Size(NormalizePercentToPx(maxWidth_, false), NormalizePercentToPx(maxHeight_, true));
        if (LessNotEqual(max.Width(), min.Width())) {
            max.SetWidth(min.Width());
        }
        if (LessNotEqual(max.Height(), min.Height())) {
            max.SetHeight(min.Height());
        }
        LayoutParam constraint = LayoutParam(max, min);
        if (!constraint.IsValid()) {
            return LayoutParam(Size(Size::INFINITE_SIZE, Size::INFINITE_SIZE), Size());
        }
        return constraint;
    }

    bool IsHidden() const
    {
        return isHidden_;
    }

    bool MustStretch() const
    {
        return mustStretch_;
    }
    DisplayType GetDisplayType() const
    {
        return displayType_;
    }

    void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
    {
        alignRules_ = alignRules;
    }

    const std::map<AlignDirection, AlignRule>& GetAlignRules() const
    {
        return alignRules_;
    }

    void SetId(const std::string& id)
    {
        id_ = id;
    }

    const std::string& GetId() const
    {
        return id_;
    }

    void SetAligned(const AlignDirection& alignDirection);

    bool GetTwoHorizontalDirectionAligned() const
    {
        return (relativeLeftAligned_ && relativeRightAligned_) || (relativeRightAligned_ && relativeMiddleAligned_) ||
            (relativeLeftAligned_ && relativeMiddleAligned_);
    }

    bool GetTwoVerticalDirectionAligned() const
    {
        return (relativeTopAligned_ && relativeCenterAligned_) || (relativeBottomAligned_ && relativeCenterAligned_) ||
            (relativeTopAligned_ && relativeBottomAligned_);
    }

    bool GetAligned(AlignDirection& alignDirection);

    double GetAlignValue(AlignDirection& alignDirection);

    void SetAlignValue(AlignDirection& alignDirection, double value);

    void Dump() override;

protected:
    void ClearRenderObject() override;
    bool MaybeRelease() override;

private:
    double flexGrow_ = 0.0;
    double flexShrink_ = 0.0;
    Dimension flexBasis_ = 0.0_px;
    bool canStretch_ = true;
    bool mustStretch_ = false;
    bool isHidden_ = false;
    RefPtr<GridColumnInfo> gridColumnInfo_;

    Dimension minWidth_ = Dimension();
    Dimension minHeight_ = Dimension();
    Dimension maxWidth_ = Dimension(Size::INFINITE_SIZE);
    Dimension maxHeight_ = Dimension(Size::INFINITE_SIZE);
    FlexAlign alignSelf_ = FlexAlign::AUTO;
    DisplayType displayType_ = DisplayType::NO_SETTING;
    std::map<AlignDirection, AlignRule> alignRules_;
    bool relativeLeftAligned_ = false;
    bool relativeRightAligned_ = false;
    bool relativeMiddleAligned_ = false;
    bool relativeTopAligned_ = false;
    bool relativeBottomAligned_ = false;
    bool relativeCenterAligned_ = false;
    double relativeLeft_ = 0.0;
    double relativeRight_ = 0.0;
    double relativeMiddle_ = 0.0;
    double relativeTop_ = 0.0;
    double relativeBottom_ = 0.0;
    double relativeCenter_ = 0.0;
    std::string id_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_RENDER_FLEX_ITEM_H
