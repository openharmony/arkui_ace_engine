/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
void ActionSheetModelNG::ShowActionSheet(const DialogProperties& arg)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);

    auto isSubContainer = container->IsSubContainer();
    auto expandDisplay = SubwindowManager::GetInstance()->GetIsExpandDisplay();
    if (!expandDisplay && isSubContainer && arg.isShowInSubWindow) {
        TAG_LOGW(AceLogTag::ACE_DIALOG, "subwindow can not show actionSheet in subwindow");
        return;
    }

    auto currentId = Container::CurrentId();
    if (expandDisplay && isSubContainer) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
    }
    ContainerScope scope(currentId);

    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (arg.dialogLevelMode == LevelMode::EMBEDDED) {
        auto embeddedOverlay = NG::DialogManager::GetEmbeddedOverlay(arg.dialogLevelUniqueId, context);
        if (embeddedOverlay) {
            overlayManager = embeddedOverlay;
        }
    }
    RefPtr<NG::FrameNode> dialog;
    if (arg.isShowInSubWindow) {
        dialog = SubwindowManager::GetInstance()->ShowDialogNG(arg, nullptr);
        CHECK_NULL_VOID(dialog);
        if (arg.isModal && !container->IsUIExtensionWindow()) {
            DialogProperties Maskarg;
            Maskarg.isMask = true;
            Maskarg.autoCancel = arg.autoCancel;
            Maskarg.onWillDismiss = arg.onWillDismiss;
            Maskarg.shadow = arg.shadow;
            auto mask = overlayManager->ShowDialog(Maskarg, nullptr, false);
            CHECK_NULL_VOID(mask);
            overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
        }
    } else {
        dialog = overlayManager->ShowDialog(arg, nullptr, false);
        CHECK_NULL_VOID(dialog);
    }
    if (SystemProperties::ConfigChangePerform()) {
        CHECK_NULL_VOID(dialog);
        auto pattern = dialog->GetPattern<OHOS::Ace::NG::DialogPattern>();
        CHECK_NULL_VOID(pattern);
        ActionSheetType type = ActionSheetType::ACTIONSHEET_TITLE;
        CreateWithOptionsResourceObj(pattern, arg.resourceTitleObj, type);
        type = ActionSheetType::ACTIONSHEET_SUBTITLE;
        CreateWithOptionsResourceObj(pattern, arg.resourceSubTitleObj, type);
        type = ActionSheetType::ACTIONSHEET_MESSAGE;
        CreateWithOptionsResourceObj(pattern, arg.resourceContentObj, type);
        type = ActionSheetType::ACTIONSHEET_BACKGROUNDCOLOR;
        CreateWithColorResourceObj(pattern, arg.resourceBgColorObj, type);
        type = ActionSheetType::ACTIONSHEET_BORDERCOLOR;
        CreateWithColorResourceObj(pattern, arg.resourceBdColorObj, type);
    }
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("onVisibleChange", "show");
}

void ActionSheetModelNG::SetAction(GestureEventFunc&& eventFunc, ActionSheetInfo& sheetInfo)
{
    sheetInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(eventFunc));
}

void ActionSheetModelNG::SetCancel(std::function<void()>&& eventFunc, DialogProperties& arg)
{
    arg.onCancel = eventFunc;
}

void ActionSheetModelNG::SetOnWillDismiss(std::function<void(const int32_t& info,
    const int32_t& instanceId)>&& onWillDismissFunc, DialogProperties& arg)
{
    arg.onWillDismiss = std::move(onWillDismissFunc);
}

void ActionSheetModelNG::SetConfirm(
    GestureEventFunc&& gestureEvent, std::function<void()>&& eventFunc, ButtonInfo& buttonInfo, DialogProperties& arg)
{
    buttonInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
}

std::string ActionSheetModelNG::DialogTypeStr(ActionSheetType type)
{
    switch (type) {
        case ActionSheetType::ACTIONSHEET_TITLE:
            return "title";
        case ActionSheetType::ACTIONSHEET_SUBTITLE:
            return "subtitle";
        case ActionSheetType::ACTIONSHEET_MESSAGE:
            return "message";
        case ActionSheetType::ACTIONSHEET_BACKGROUNDCOLOR:
            return "backgroundColor";
        case ActionSheetType::ACTIONSHEET_BORDERCOLOR:
            return "borderColor";
        default:
            break;
    }
}

void ActionSheetModelNG::UpdateActionSheetType(
    const RefPtr<NG::DialogPattern>& pattern, ActionSheetType type, std::string result)
{
    CHECK_NULL_VOID(pattern);
    Color color = Color::ColorFromString(result);
    switch (type) {
        case ActionSheetType::ACTIONSHEET_TITLE:
        case ActionSheetType::ACTIONSHEET_SUBTITLE:
        case ActionSheetType::ACTIONSHEET_MESSAGE:
            pattern->UpdateContent(result, type);
            break;
        case ActionSheetType::ACTIONSHEET_BACKGROUNDCOLOR:
        case ActionSheetType::ACTIONSHEET_BORDERCOLOR:
            pattern->UpdateContent(color, type);
            break;
        default:
            break;
    }
}

void ActionSheetModelNG::CreateWithOptionsResourceObj(const RefPtr<OHOS::Ace::NG::DialogPattern>& pattern,
    const RefPtr<ResourceObject>& textColorResObj, ActionSheetType type)
{
    CHECK_NULL_VOID(pattern);
    std::string key = "ActionSheetDialog" + DialogTypeStr(type);
    if (!textColorResObj) {
        pattern->RemoveResObj(key);
        return;
    }
    CHECK_NULL_VOID(textColorResObj);
    auto&& updateFunc = [pattern, type](const RefPtr<ResourceObject>& textColorResObj) {
        std::string result;
        if (!ResourceParseUtils::ParseResString(textColorResObj, result)) {
            return;
        }
        ActionSheetModelNG::UpdateActionSheetType(pattern, type, result);
    };
    updateFunc(textColorResObj);
    pattern->AddResObj(key, textColorResObj, std::move(updateFunc));
}

void ActionSheetModelNG::CreateWithColorResourceObj(const RefPtr<OHOS::Ace::NG::DialogPattern>& pattern,
    const RefPtr<ResourceObject>& textColorResObj, ActionSheetType type)
{
    CHECK_NULL_VOID(pattern);
    std::string key = "ActionSheetDialog" + DialogTypeStr(type);
    if (!textColorResObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [pattern, type](const RefPtr<ResourceObject>& textColorResObj) {
        Color result;
        if (!ResourceParseUtils::ParseResColor(textColorResObj, result)) {
            return;
        }
        ActionSheetModelNG::UpdateActionSheetType(pattern, type, result.ColorToString());
    };
    updateFunc(textColorResObj);
    pattern->AddResObj(key, textColorResObj, std::move(updateFunc));
}
} // namespace OHOS::Ace::NG
