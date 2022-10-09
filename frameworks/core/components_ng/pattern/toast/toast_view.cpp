/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/toast/toast_view.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> ToastView::CreateToastNode(
    const std::string& message, const std::string& bottom, bool isRightToLeft)
{
    auto context = PipelineContext::GetCurrentContext();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    LOGI("begin to show toast, toast id is %{public}d, message is %{public}s", toastId, message.c_str());

    // make toast node
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<TextPattern>());
    auto layoutProperty = toastNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(toastContext, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto toastTheme = themeManager->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, nullptr);

    // update toast props
    auto rootHeight = Dimension(context->GetRootHeight());
    auto bottomPosition = Dimension(StringUtils::StringToDimension(bottom, true).ConvertToPx());
    if (bottomPosition > rootHeight) {
        bottomPosition = rootHeight;
    }
    Color textColor;
    Color toastBackgroundColor;
    Dimension fontSize;
    Dimension minWidth;
    Dimension maxWidth;
    Dimension minHeight;
    FontWeight fontWeight;
    Dimension toastbottom;
    BorderRadiusProperty borderRadius;

    toastBackgroundColor = toastTheme->GetBackgroundColor();
    fontWeight = toastTheme->GetTextStyle().GetFontWeight();
    textColor = toastTheme->GetTextStyle().GetTextColor();
    fontSize = toastTheme->GetTextStyle().GetFontSize();
    minWidth = Dimension(toastTheme->GetMinWidth().ConvertToPx());
    maxWidth = Dimension(toastTheme->GetMaxWidth().ConvertToPx());
    minHeight = Dimension(toastTheme->GetMinHeight().ConvertToPx());
    toastbottom = Dimension(bottomPosition.IsValid() ? bottomPosition.Value() : toastTheme->GetBottom().ConvertToPx());
    auto radius = toastTheme->GetRadius();
    borderRadius.SetRadius(Dimension(radius.GetX()));

    layoutProperty->UpdateContent(message);
    layoutProperty->UpdateTextColor(textColor);
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    layoutProperty->UpdateFontWeight(fontWeight);
    layoutProperty->UpdateFontSize(fontSize);
    layoutProperty->UpdateCalcMaxSize(CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    layoutProperty->UpdateCalcMinSize(CalcSize(NG::CalcLength(minWidth), NG::CalcLength(minHeight)));
    layoutProperty->UpdateLayoutDirection((isRightToLeft ? TextDirection::RTL : TextDirection::LTR));

    toastContext->UpdateBackgroundColor(toastBackgroundColor);
    toastContext->UpdateBorderRadius(borderRadius);
    toastContext->UpdateBackShadow(ShadowConfig::DefaultShadowL);
    toastContext->UpdateOffset(OffsetT<Dimension>(0.0_px, rootHeight / 2.0 - toastbottom));

    return toastNode;
}

} // namespace OHOS::Ace::NG