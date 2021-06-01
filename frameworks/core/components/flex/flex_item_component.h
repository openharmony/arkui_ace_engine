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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_FLEX_ITEM_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_FLEX_ITEM_COMPONENT_H

#include "core/components/flex/flex_item_element.h"
#include "core/components/flex/render_flex_item.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class FlexItemComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(FlexItemComponent, SoleChildComponent);

public:
    FlexItemComponent(double flexGrow, double flexShrink, double flexBasis)
        : flexGrow_(flexGrow), flexShrink_(flexShrink), flexBasis_(flexBasis) {};
    FlexItemComponent(double flexGrow, double flexShrink, double flexBasis, const RefPtr<Component>& child)
        : SoleChildComponent(child), flexGrow_(flexGrow), flexShrink_(flexShrink), flexBasis_(flexBasis) {}
    ~FlexItemComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderFlexItem::Create();
    }

    RefPtr<Element> CreateElement() override
    {
        return AceType::MakeRefPtr<FlexItemElement>();
    }

    double GetFlexGrow() const
    {
        return flexGrow_;
    }

    double GetFlexShrink() const
    {
        return flexShrink_;
    }

    double GetFlexBasis() const
    {
        return flexBasis_;
    }

    void SetFlexGrow(double flexGrow)
    {
        flexGrow_ = flexGrow;
    }

    void SetFlexShrink(double flexShrink)
    {
        flexShrink_ = flexShrink;
    }

    void SetFlexBasis(double flexBasis)
    {
        flexBasis_ = flexBasis;
    }

    bool GetStretchFlag() const
    {
        return canStretch_;
    }

    void SetStretchFlag(bool canStretch)
    {
        canStretch_ = canStretch;
    }

    FlexAlign GetAlignSelf() const
    {
        return alignSelf_;
    }

    void SetAlignSelf(FlexAlign alignSelf)
    {
        alignSelf_ = alignSelf;
    }

    const LayoutParam& GetConstraints() const
    {
        return constraints_;
    }

    void SetConstraints(const LayoutParam& constraints)
    {
        constraints_ = constraints;
    }

    const Dimension& GetMinWidth() const
    {
        return minWidth_;
    }

    void SetMinWidth(const Dimension& minWidth)
    {
        minWidth_ = minWidth;
    }

    const Dimension& GetMinHeight() const
    {
        return minHeight_;
    }

    void SetMinHeight(const Dimension& minHeight)
    {
        minHeight_ = minHeight;
    }

    const Dimension& GetMaxWidth() const
    {
        return maxWidth_;
    }

    void SetMaxWidth(const Dimension& maxWidth)
    {
        maxWidth_ = maxWidth;
    }

    const Dimension& GetMaxHeight() const
    {
        return maxHeight_;
    }

    void SetMaxHeight(const Dimension& maxHeight)
    {
        maxHeight_ = maxHeight;
    }

    bool IsHidden() const
    {
        return isHidden_;
    }

    void SetIsHidden(bool isHidden)
    {
        isHidden_ = isHidden;
    }

private:
    double flexGrow_ = 0.0;
    double flexShrink_ = 0.0;
    double flexBasis_ = 0.0;
    bool canStretch_ = true; // When width or height is set, this item can not be stretched.

    LayoutParam constraints_;
    Dimension minWidth_ = Dimension();
    Dimension minHeight_ = Dimension();
    Dimension maxWidth_ = Dimension(Size::INFINITE_SIZE);
    Dimension maxHeight_ = Dimension(Size::INFINITE_SIZE);
    bool isHidden_ = false;

    FlexAlign alignSelf_ = FlexAlign::AUTO;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FLEX_FLEX_ITEM_COMPONENT_H
