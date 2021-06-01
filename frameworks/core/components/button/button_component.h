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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_COMPONENT_H

#include "base/geometry/dimension.h"
#include "base/utils/label_target.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border_edge.h"
#include "core/components/common/properties/color.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/measurable.h"

namespace OHOS::Ace {

// Layout size extend to max which is specified by parent node when rendering.
constexpr int32_t LAYOUT_FLAG_EXTEND_TO_PARENT = 1;

using ProgressCallback = std::function<void(uint32_t)>;

class ButtonProgressController : public virtual AceType {
    DECLARE_ACE_TYPE(ButtonProgressController, AceType);

public:
    void SetProgress(uint32_t progress)
    {
        if (progressCallback_) {
            progressCallback_(progress);
        }
    }

    void SetProgressCallback(const ProgressCallback& progressCallback)
    {
        progressCallback_ = progressCallback;
    }

private:
    ProgressCallback progressCallback_;
};

class ACE_EXPORT ButtonComponent : public ComponentGroup, public LabelTarget, public Measurable {
    DECLARE_ACE_TYPE(ButtonComponent, ComponentGroup, LabelTarget, Measurable);

public:
    explicit ButtonComponent(const std::list<RefPtr<Component>>& children);
    ~ButtonComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    ButtonType GetType() const
    {
        return type_;
    }

    bool GetDisabledState() const
    {
        return isDisabled_;
    }

    bool GetWaitingState() const
    {
        return isWaiting_;
    }

    const Dimension& GetMinWidth() const
    {
        return minWidth_;
    }

    const Dimension& GetRectRadius() const
    {
        return rrectRadius_;
    }

    const Dimension& GetProgressDiameter() const
    {
        return progressDiameter_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetClickedColor() const
    {
        return clickedColor_;
    }

    const Color& GetDisabledColor() const
    {
        return disabledColor_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetProgressColor() const
    {
        return progressColor_;
    }

    const Color& GetProgressFocusColor() const
    {
        return progressFocusColor_;
    }

    const Color& GetFocusAnimationColor() const
    {
        return focusAnimationColor_;
    }

    const BorderEdge& GetBorderEdge() const
    {
        return borderEdge_;
    }

    const EventMarker& GetClickedEventId() const
    {
        return clickEventId_;
    }

    bool GetAutoFocusState() const
    {
        return isAutoFocus_;
    }

    bool GetFocusable() const
    {
        return focusable_;
    }

    void SetType(ButtonType type)
    {
        type_ = type;
    }

    void SetDisabledState(bool state)
    {
        isDisabled_ = state;
    }

    void SetWaitingState(bool state)
    {
        isWaiting_ = state;
    }

    void SetMinWidth(const Dimension& width)
    {
        minWidth_ = width;
    }

    void SetRectRadius(const Dimension& radius)
    {
        rrectRadius_ = radius;
    }

    void SetProgressDiameter(const Dimension& diameter)
    {
        progressDiameter_ = diameter;
    }

    void SetBackgroundColor(const Color& color)
    {
        backgroundColor_ = color;
    }

    void SetClickedColor(const Color& color)
    {
        clickedColor_ = color;
    }

    void SetDisabledColor(const Color& color)
    {
        disabledColor_ = color;
    }

    void SetFocusColor(const Color& color)
    {
        focusColor_ = color;
    }

    void SetHoverColor(const Color& color)
    {
        hoverColor_ = color;
    }

    void SetProgressColor(const Color& color)
    {
        progressColor_ = color;
    }

    void SetProgressFocusColor(const Color& color)
    {
        progressFocusColor_ = color;
    }

    void SetFocusAnimationColor(const Color& color)
    {
        focusAnimationColor_ = color;
    }

    void SetBorderEdge(const BorderEdge& borderEdge)
    {
        borderEdge_ = borderEdge;
    }

    void SetClickedEventId(const EventMarker& eventId)
    {
        clickEventId_ = eventId;
    }

    void SetAutoFocusState(bool isAutoFocus)
    {
        isAutoFocus_ = isAutoFocus;
    }

    void SetFocusable(bool focusable)
    {
        focusable_ = focusable;
    }

    RefPtr<ButtonProgressController> GetButtonController() const
    {
        return buttonController_;
    }

    uint32_t GetLayoutFlag() const
    {
        return layoutFlag_;
    }

    void SetLayoutFlag(uint32_t flag)
    {
        layoutFlag_ = flag;
    }

    bool IsInnerBorder() const
    {
        return isInnerBorder_;
    }

    void SetIsInnerBorder(bool isInnerBorder)
    {
        isInnerBorder_ = isInnerBorder;
    }

private:
    ButtonType type_ { ButtonType::NORMAL };
    Color backgroundColor_;
    Color clickedColor_;
    Color disabledColor_;
    Color focusColor_ = Color::WHITE;
    Color focusAnimationColor_ = Color::WHITE;
    Color hoverColor_;
    Color progressColor_;
    Color progressFocusColor_;
    BorderEdge borderEdge_ { Color(0xff000000), Dimension(), BorderStyle::NONE };
    EventMarker clickEventId_;

    bool isInnerBorder_ = false;
    bool isDisabled_ = false;
    bool isWaiting_ = false;
    bool isAutoFocus_ = false;
    bool focusable_ = true;
    Dimension minWidth_;
    Dimension rrectRadius_;
    Dimension progressDiameter_;
    RefPtr<ButtonProgressController> buttonController_;
    uint32_t layoutFlag_ = 0;
};

class ButtonBuilder {
public:
    static RefPtr<ButtonComponent> Build(const RefPtr<ThemeManager>& themeManager, const std::string& text);
    static RefPtr<ButtonComponent> Build(const RefPtr<ThemeManager>& themeManager, const std::string& text,
        TextStyle& textStyle, const Color& textFocusColor = Color(), bool useTextFocus = false);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_COMPONENT_H
