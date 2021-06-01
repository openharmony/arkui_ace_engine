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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H

#include "core/components/box/box_base_component.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace {

enum class HoverAnimationType : int32_t {
    NONE,
    OPACITY,
    SCALE,
};

// A component can box others components.
class ACE_EXPORT BoxComponent : public BoxBaseComponent {
    DECLARE_ACE_TYPE(BoxComponent, BoxBaseComponent);

public:
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Decoration> GetBackDecoration() const
    {
        return backDecoration_;
    }

    RefPtr<Decoration> GetFrontDecoration() const
    {
        return frontDecoration_;
    }

    const Color& GetColor() const
    {
        if (backDecoration_) {
            return backDecoration_->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    }

    bool GetDecorationUpdateFlag() const
    {
        return decorationUpdateFlag_;
    }

    HoverAnimationType GetMouseAnimationType() const
    {
        return animationType_;
    }

    void SetBackDecoration(const RefPtr<Decoration>& decoration)
    {
        backDecoration_ = decoration;
        SetDecorationUpdateFlag(true);
    }

    void SetFrontDecoration(const RefPtr<Decoration>& decoration)
    {
        frontDecoration_ = decoration;
        SetDecorationUpdateFlag(true);
    }

    void SetColor(const Color& color)
    {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        backDecoration_->SetBackgroundColor(color);
    }

    void SetDecorationUpdateFlag(bool flag)
    {
        decorationUpdateFlag_ = flag;
    }

    void SetMouseAnimationType(HoverAnimationType animationType)
    {
        animationType_ = animationType;
    }

    void SetOverflow(Overflow overflow)
    {
        overflow_ = overflow;
    }

    Overflow GetOverflow() const
    {
        return overflow_;
    }

private:
    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    bool decorationUpdateFlag_ = false;
    HoverAnimationType animationType_ = HoverAnimationType::NONE;
    Overflow overflow_ = Overflow::OBSERVABLE;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
