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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_DISPLAY_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_DISPLAY_COMPONENT_H

#include "core/components/display/display_element.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

enum class VisibleType {
    VISIBLE,
    INVISIBLE,
    GONE,
};

class ACE_EXPORT DisplayComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(DisplayComponent, SoleChildComponent);

public:
    DisplayComponent() = default;
    explicit DisplayComponent(const RefPtr<Component>& child) : SoleChildComponent(child) {}
    ~DisplayComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Element> CreateElement() override
    {
        return AceType::MakeRefPtr<DisplayElement>();
    }

    VisibleType GetVisible() const
    {
        return visible_;
    }

    double GetOpacity() const
    {
        return opacity_;
    }

    void SetVisible(VisibleType visible)
    {
        visible_ = visible;
    }

    void SetOpacity(double opacity)
    {
        opacity_ = opacity;
    }

    void DisableLayer(bool disable)
    {
        disableLayer_ = disable;
    }

    bool IsDisableLayer() const
    {
        return disableLayer_;
    }

    void SetShadow(const Shadow& shadow)
    {
        shadow_ = shadow;
    }

    const Shadow& GetShadow() const
    {
        return shadow_;
    }

private:
    VisibleType visible_ = VisibleType::VISIBLE;
    Shadow shadow_;
    double opacity_ = 1.0;
    bool disableLayer_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_DISPLAY_COMPONENT_H
