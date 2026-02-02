/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "base/utils/date_util.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

namespace OHOS::Ace::NG {

void ShowCalendarPickerDialog(const CalendarPickerDialogOption* option)
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    CHECK_NULL_VOID(option);
    const DialogProperties* dialogPropertiesPtr = reinterpret_cast<const DialogProperties*>(option->dialogProperties);
    const CalendarSettingData* settingDataPtr = reinterpret_cast<const CalendarSettingData*>(option->settingData);
    const std::map<std::string, NG::DialogEvent>* dialogEventPtr =
        reinterpret_cast<const std::map<std::string, NG::DialogEvent>*>(option->dialogEvent);
    const std::map<std::string, NG::DialogGestureEvent>* dialogCancelEventPtr =
        reinterpret_cast<const std::map<std::string, NG::DialogGestureEvent>*>(option->dialogCancelEvent);
    const std::map<std::string, NG::DialogCancelEvent>* dialogLifeCycleEventPtr =
        reinterpret_cast<const std::map<std::string, NG::DialogCancelEvent>*>(option->dialogLifeCycleEvent);
    const std::vector<ButtonInfo>* buttonInfosPtr =
        reinterpret_cast<const std::vector<ButtonInfo>*>(option->buttonInfos);

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;

    executor->PostTask(
        [dialogProperties = *dialogPropertiesPtr, settingData = *settingDataPtr, dialogEvent = *dialogEventPtr,
            dialogCancelEvent = *dialogCancelEventPtr, dialogLifeCycleEvent = *dialogLifeCycleEventPtr,
            buttonInfos = *buttonInfosPtr, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowCalendarDialog(
                dialogProperties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowCalendarPicker",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void JSRemoveResObj(ArkUI_CharPtr key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

ArkUI_Bool CheckOrientationChange()
{
    return CalendarDialogView::CheckOrientationChange();
}

const ArkUICalendarPickerDialogModifier* GetCalendarPickerDialogDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICalendarPickerDialogModifier modifier = {
        .show = ShowCalendarPickerDialog,
        .jsRemoveResObj = JSRemoveResObj,
        .checkOrientationChange = CheckOrientationChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUICalendarPickerDialogModifier* GetCJUICalendarPickerDialogModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICalendarPickerDialogModifier modifier = {
        .show = ShowCalendarPickerDialog,
        .jsRemoveResObj = JSRemoveResObj,
        .checkOrientationChange = CheckOrientationChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG