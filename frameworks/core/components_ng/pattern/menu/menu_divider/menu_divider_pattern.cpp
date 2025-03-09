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

#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"

#include "core/components/select/select_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<NodePaintMethod> MenuDividerPattern::CreateNodePaintMethod()
{
    if (!paintMethod_) {
        paintMethod_ = MakeRefPtr<MenuDividerPaintMethod>();
    }
    auto context = GetContext();
    CHECK_NULL_RETURN(context, paintMethod_);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(context, paintMethod_);
    auto themeOutPadding = static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()) -
                           static_cast<float>(theme->GetOutPadding().ConvertToPx());
    auto themeIconPadding = static_cast<float>(theme->GetIconSideLength().ConvertToPx()) +
                            static_cast<float>(theme->GetIconContentPadding().ConvertToPx());
    paintMethod_->SetThemeOutPadding(themeOutPadding);
    paintMethod_->SetThemeIconPadding(themeIconPadding);
    paintMethod_->SetThemeDividerColor(theme->GetLineColor());
    paintMethod_->SetThemeHorInterval(theme->GetMenuItemHorIntervalPadding().ConvertToPx());
    paintMethod_->SetThemeStrokeWidth(theme->GetDefaultDividerWidth().ConvertToPx());
    paintMethod_->SetDefaultShowDivider(theme->GetDefaultShowDivider());
    paintMethod_->SetIsOption(isOption_);
    return paintMethod_;
}

RefPtr<LayoutAlgorithm> MenuDividerPattern::CreateLayoutAlgorithm()
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    return MakeRefPtr<MenuDividerLayoutAlgorithm>(theme->GetDefaultDividerWidth());
}

bool MenuDividerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG
