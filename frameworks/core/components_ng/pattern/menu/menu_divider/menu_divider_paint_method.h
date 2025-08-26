/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_PAINT_METHOD_H

#include "core/components_ng/pattern/menu/menu_divider/menu_divider_modifier.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuDividerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(MenuDividerPaintMethod, NodePaintMethod);
public:
    MenuDividerPaintMethod() {}
    ~MenuDividerPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CreateContentModifier();
        UpdateModfierParams(paintWrapper);
        return dividerModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CreateContentModifier();
        UpdateModfierParams(paintWrapper);
    }

    void SetThemeOutPadding(float themeOutPadding)
    {
        themeOutPadding_ = themeOutPadding;
    }

    void SetThemeIconPadding(float themeIconPadding)
    {
        themeIconPadding_ = themeIconPadding;
    }

    void SetThemeDividerColor(Color themeDividerColor)
    {
        themeDividerColor_ = themeDividerColor;
    }

    void SetThemeStrokeWidth(float themeStrokeWidth)
    {
        themeStrokeWidth_ = themeStrokeWidth;
    }

    void SetThemeHorInterval(float themeHorInterval)
    {
        themeHorInterval_ = themeHorInterval;
    }

    void SetDefaultShowDivider(bool defaultShowDivider)
    {
        defaultShowDivider_ = defaultShowDivider;
    }

    void SetIsOption(bool isOption)
    {
        isOption_ = isOption;
    }

private:
    void CreateContentModifier();

    void UpdateModfierParams(PaintWrapper* paintWrapper);
    void GetDividerMargin(
        float& startMargin, float& endMargin, const RefPtr<MenuDividerPaintProperty>& paintProperty, const SizeF& size);

    RefPtr<MenuDividerModifier> dividerModifier_ = nullptr;
    float themeStrokeWidth_ = 0.0f;
    Color themeDividerColor_ = Color::TRANSPARENT;
    float themeOutPadding_ = 0.0f;
    float themeIconPadding_ = 0.0f;
    float themeHorInterval_ = 0.0f;
    bool defaultShowDivider_ = false;
    bool isOption_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(MenuDividerPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_PAINT_METHOD_H
