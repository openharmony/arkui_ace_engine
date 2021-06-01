/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_BASE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_BASE_COMPONENT_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/edge.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/measurable.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

constexpr uint32_t PERCENT_FLAG_USE_VIEW_PORT = 1;

// A component can box other components.
class BoxBaseComponent : public SoleChildComponent, public Measurable {
    DECLARE_ACE_TYPE(BoxBaseComponent, SoleChildComponent, Measurable);

public:
    const Alignment& GetAlignment() const
    {
        return align_;
    }

    const LayoutParam& GetConstraints() const
    {
        return constraints_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Edge& GetMargin() const
    {
        return margin_;
    }

    const Edge& GetAdditionalMargin() const
    {
        return additionalMargin_;
    }

    const Dimension& GetWidthDimension() const
    {
        return GetWidth();
    }

    const Dimension& GetHeightDimension() const
    {
        return GetHeight();
    }

    BoxFlex GetFlex() const
    {
        return flex_;
    }

    bool GetDeliverMinToChild() const
    {
        return deliverMinToChild_;
    }

    bool GetScrollPage() const
    {
        return scrollPage_;
    }

    uint32_t GetPercentFlag() const
    {
        return percentFlag_;
    }

    bool GetLayoutInBoxFlag() const
    {
        return layoutInBox_;
    }

    void SetAlignment(const Alignment& alignment)
    {
        align_ = alignment;
    }

    void SetConstraints(const LayoutParam& constraints)
    {
        if (!constraints.IsWidthValid() || !constraints.IsHeightValid()) {
            return;
        }
        constraints_ = constraints;
    }

    void SetPadding(const Edge& padding)
    {
        if (padding.IsValid()) {
            padding_ = padding;
        }
    }

    void SetMargin(const Edge& margin, const Edge& additionalMargin = Edge())
    {
        margin_ = margin;
        if (additionalMargin.IsValid()) {
            additionalMargin_ = additionalMargin;
        }
    }

    void SetFlex(BoxFlex flex)
    {
        flex_ = flex;
    }

    void SetDeliverMinToChild(bool deliverMinToChild)
    {
        deliverMinToChild_ = deliverMinToChild;
    }

    void SetScrollPage(bool scrollPage)
    {
        scrollPage_ = scrollPage;
    }

    void SetPercentFlag(uint32_t flag)
    {
        percentFlag_ = flag;
    }

    void SetLayoutInBoxFlag(bool layoutInBox)
    {
        layoutInBox_ = layoutInBox;
    }

    void SetAspectRatio(double aspectRatio)
    {
        aspectRatio_ = aspectRatio;
    }

    double GetAspectRatio() const
    {
        return aspectRatio_;
    }

    void SetMinWidth(const Dimension& minWidth)
    {
        minWidth_ = minWidth;
    }

    const Dimension& GetMinWidth() const
    {
        return minWidth_;
    }

    void SetMinHeight(const Dimension& minHeight)
    {
        minHeight_ = minHeight;
    }

    const Dimension& GetMinHeight() const
    {
        return minHeight_;
    }

    void SetMaxWidth(const Dimension& maxWidth)
    {
        maxWidth_ = maxWidth;
    }

    const Dimension& GetMaxWidth() const
    {
        return maxWidth_;
    }

    void SetMaxHeight(const Dimension& maxHeight)
    {
        maxHeight_ = maxHeight;
    }

    const Dimension& GetMaxHeight() const
    {
        return maxHeight_;
    }

    const RefPtr<GridLayoutInfo>& GetGridLayoutInfo() const
    {
        return gridLayoutInfo_;
    }

    void SetGridLayoutInfo(const RefPtr<GridLayoutInfo>& gridLayoutInfo)
    {
        gridLayoutInfo_ = gridLayoutInfo;
    }

    void SetUseLiteStyle(bool flag)
    {
        useLiteStyle_ = flag;
    }

    bool UseLiteStyle() const
    {
        return useLiteStyle_;
    }

private:
    Alignment align_;
    LayoutParam constraints_ = LayoutParam(Size(), Size()); // no constraints when init
    Edge padding_;
    Edge margin_;
    Edge additionalMargin_;
    BoxFlex flex_ { BoxFlex::FLEX_NO };
    bool deliverMinToChild_ = true;
    bool scrollPage_ = false;
    uint32_t percentFlag_ = 1;
    bool layoutInBox_ = false;
    double aspectRatio_ = 0.0;
    Dimension minWidth_ = Dimension();
    Dimension minHeight_ = Dimension();
    Dimension maxWidth_ = Dimension();
    Dimension maxHeight_ = Dimension();
    RefPtr<GridLayoutInfo> gridLayoutInfo_;
    bool useLiteStyle_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_BASE_COMPONENT_H
