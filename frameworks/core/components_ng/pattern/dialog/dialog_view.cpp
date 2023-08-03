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
#include "core/components_ng/pattern/dialog/dialog_view.h"

#include <optional>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
void ProcessMaskRect(const DialogProperties& param, const RefPtr<FrameNode>& dialog)
{
    auto dialogContext = dialog->GetRenderContext();
    auto hub = dialog->GetEventHub<DialogEventHub>();
    if (param.maskRect.has_value()) {
        RectF rect = RectF(param.maskRect->GetOffset().GetX().ConvertToPx(),
                           param.maskRect->GetOffset().GetY().ConvertToPx(),
                           param.maskRect->GetWidth().ConvertToPx(), param.maskRect->GetHeight().ConvertToPx());
        dialogContext->ClipWithRect(rect);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        std::vector<DimensionRect> mouseResponseRegion;
        mouseResponseRegion.push_back(param.maskRect.value());
        gestureHub->SetMouseResponseRegion(mouseResponseRegion);
        gestureHub->SetResponseRegion(mouseResponseRegion);
    }
}
}

RefPtr<FrameNode> DialogView::CreateDialogNode(
    const DialogProperties& param, const RefPtr<UINode>& customNode = nullptr)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);

    std::string tag;
    switch (param.type) {
        case DialogType::ALERT_DIALOG: {
            tag = V2::ALERT_DIALOG_ETS_TAG;
            break;
        }
        case DialogType::ACTION_SHEET: {
            tag = V2::ACTION_SHEET_DIALOG_ETS_TAG;
            break;
        }
        default:
            tag = V2::DIALOG_ETS_TAG;
            break;
    }
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(dialogTheme, customNode));

    // update layout and render props
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
    CHECK_NULL_RETURN(dialogLayoutProp, dialog);
    dialogLayoutProp->UpdateDialogAlignment(param.alignment);
    dialogLayoutProp->UpdateDialogOffset(param.offset);
    dialogLayoutProp->UpdateGridCount(param.gridCount);
    dialogLayoutProp->UpdateUseCustomStyle(param.customStyle);
    dialogLayoutProp->UpdateAutoCancel(param.autoCancel);
    dialogLayoutProp->UpdateShowInSubWindow(param.isShowInSubWindow);
    // create gray background
    auto dialogContext = dialog->GetRenderContext();
    CHECK_NULL_RETURN(dialogContext, dialog);
    dialogContext->UpdateBackgroundColor(param.maskColor.value_or(dialogTheme->GetMaskColorEnd()));

    // set onCancel callback
    auto hub = dialog->GetEventHub<DialogEventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    hub->SetOnCancel(param.onCancel);
    hub->SetOnSuccess(param.onSuccess);

    ProcessMaskRect(param, dialog);

    auto pattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->BuildChild(param);

    // set open and close animation
    pattern->SetOpenAnimation(param.openAnimation);
    pattern->SetCloseAnimation(param.closeAnimation);

    pattern->SetDialogProperties(param);

    dialog->MarkModifyDone();
    return dialog;
}

} // namespace OHOS::Ace::NG
