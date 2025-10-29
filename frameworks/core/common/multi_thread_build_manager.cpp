/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/common/multi_thread_build_manager.h"

#include <unordered_set>

#ifdef FFRT_SUPPORT
#include "ffrt_inner.h"
#endif
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
#ifdef FFRT_SUPPORT
constexpr uint32_t MAX_THREAD_NUM = 3;
constexpr uint32_t ASYNC_UITASK_QOS = 5;
std::unique_ptr<ffrt::queue> asyncUITaskQueue = nullptr;
#endif
} // namespace
thread_local bool MultiThreadBuildManager::isThreadSafeNodeScope_ = false;
thread_local bool MultiThreadBuildManager::isUIThread_ = false;
thread_local bool MultiThreadBuildManager::isParallelizeUI_ = false;

MultiThreadBuildManager& MultiThreadBuildManager::GetInstance()
{
    static MultiThreadBuildManager MultiThreadBuildManager;
    return MultiThreadBuildManager;
}

MultiThreadBuildManager::MultiThreadBuildManager()
{
    InitAsyncUITaskQueue();
}

void MultiThreadBuildManager::InitOnUIThread()
{
    isUIThread_ = true;
}

void MultiThreadBuildManager::InitAsyncUITaskQueue()
{
#ifdef FFRT_SUPPORT
    asyncUITaskQueue = std::make_unique<ffrt::queue>(
        ffrt::queue_concurrent, "ArkUIAsyncUITask", ffrt::queue_attr().max_concurrency(MAX_THREAD_NUM));
#endif
}

bool MultiThreadBuildManager::IsOnUIThread()
{
    return isUIThread_;
}

bool MultiThreadBuildManager::CheckOnUIThread()
{
    if (!IsOnUIThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckOnUIThread failed");
        return false;
    }
    return true;
}

bool MultiThreadBuildManager::CheckNodeOnValidThread(NG::UINode* node)
{
    if (!node) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckNodeOnValidThread failed. node is nullptr");
        return false;
    }
    if (!node->IsFree() && !MultiThreadBuildManager::IsOnUIThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckNodeOnValidThread failed. unfree node not run on main thread");
        return false;
    }
    return true;
}

void MultiThreadBuildManager::SetIsThreadSafeNodeScope(bool isThreadSafeNodeScope)
{
    isThreadSafeNodeScope_ = isThreadSafeNodeScope;
}

bool MultiThreadBuildManager::IsThreadSafeNodeScope()
{
    return isThreadSafeNodeScope_ || SystemProperties::GetDebugThreadSafeNodeEnabled();
}

bool MultiThreadBuildManager::IsParallelScope()
{
    return isThreadSafeNodeScope_ && isParallelizeUI_;
}

bool MultiThreadBuildManager::PostAsyncUITask(
    int32_t contextId, std::function<void()>&& asyncUITask, std::function<void()>&& onFinishTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
#ifdef FFRT_SUPPORT
    if (!asyncUITaskQueue) {
        return false;
    }
    auto result = asyncUITaskQueue->submit_h(
        [contextId, asyncUITask = std::move(asyncUITask), onFinishTask = std::move(onFinishTask)]() {
            ContainerScope scope(contextId);
            asyncUITask();
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [contextId, onFinishTask = std::move(onFinishTask)]() {
                    ContainerScope scope(contextId);
                    onFinishTask();
                },
                TaskExecutor::TaskType::UI, "ArkUIAsyncUIOnFinishTask", PriorityType::IMMEDIATE);
        },
        ffrt::task_attr().qos(ASYNC_UITASK_QOS));
    return result != nullptr;
#else
    return taskExecutor->PostTask(
        [contextId, asyncUITask = std::move(asyncUITask), onFinishTask = std::move(onFinishTask)]() {
            ContainerScope scope(contextId);
            asyncUITask();
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [contextId, onFinishTask = std::move(onFinishTask)]() {
                    ContainerScope scope(contextId);
                    onFinishTask();
                },
                TaskExecutor::TaskType::UI, "ArkUIAsyncUIOnFinishTask", PriorityType::IMMEDIATE);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIAsyncUITask");
#endif
}

bool MultiThreadBuildManager::PostUITask(int32_t contextId, std::function<void()>&& uiTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask(
        [contextId, uiTask = std::move(uiTask)]() {
            ContainerScope scope(contextId);
            uiTask();
        },
        TaskExecutor::TaskType::UI, "ArkUISyncUITask", PriorityType::IMMEDIATE);
}

bool MultiThreadBuildManager::PostUITaskAndWait(int32_t contextId, std::function<void()>&& uiTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostSyncTask(
        [contextId, uiTask = std::move(uiTask)]() {
            ContainerScope scope(contextId);
            uiTask();
        },
        TaskExecutor::TaskType::UI, "ArkUISyncTaskAndWait", PriorityType::IMMEDIATE);
}

void MultiThreadBuildManager::CheckTag(const std::string& tag)
{
    if (!isParallelizeUI_) {
        return;
    }
    static std::unordered_set<std::string> supportTags { V2::COLUMN_ETS_TAG, V2::IMAGE_ETS_TAG, V2::ROW_ETS_TAG,
        V2::RELATIVE_CONTAINER_ETS_TAG, V2::TEXT_ETS_TAG, V2::STACK_ETS_TAG, V2::BUTTON_ETS_TAG, V2::TOGGLE_ETS_TAG,
        V2::LIST_ETS_TAG, V2::LIST_ITEM_ETS_TAG, V2::GRID_ETS_TAG, V2::GRID_ITEM_ETS_TAG, V2::COMMON_VIEW_ETS_TAG,
        V2::CALENDAR_PICKER_ETS_TAG, V2::TEXT_PICKER_ETS_TAG, V2::PATTERN_LOCK_ETS_TAG, V2::DATE_PICKER_ETS_TAG,
        V2::TIME_PICKER_ETS_TAG, V2::GAUGE_ETS_TAG, V2::DATA_PANEL_ETS_TAG, V2::PROGRESS_ETS_TAG, V2::COUNTER_ETS_TAG,
        V2::IMAGE_ANIMATOR_ETS_TAG, V2::LOADING_PROGRESS_ETS_TAG, V2::SIDE_BAR_ETS_TAG, V2::NAVIGATION_VIEW_ETS_TAG,
        V2::NAVBAR_ETS_TAG, V2::TITLE_BAR_ETS_TAG, V2::NAVBAR_CONTENT_ETS_TAG, V2::TOOL_BAR_ETS_TAG,
        V2::NAVIGATION_CONTENT_ETS_TAG, V2::DIVIDER_ETS_TAG, V2::BAR_ITEM_ETS_TAG, V2::NAVIGATION_MENU_ETS_TAG,
        V2::BACK_BUTTON_ETS_TAG, V2::BACK_BUTTON_IMAGE_ETS_TAG, V2::SPLIT_PLACEHOLDER_CONTENT_ETS_TAG,
        V2::PRIMARY_CONTENT_NODE_ETS_TAG, V2::STEPPER_ETS_TAG, V2::STEPPER_ITEM_ETS_TAG, V2::MENU_ETS_TAG,
        V2::MENU_ITEM_ETS_TAG, V2::MENU_ITEM_GROUP_ETS_TAG, V2::MENU_WRAPPER_ETS_TAG, V2::MENU_PREVIEW_ETS_TAG,
        V2::ALERT_DIALOG_ETS_TAG, V2::ACTION_SHEET_DIALOG_ETS_TAG, V2::CUSTOM_DIALOG_ETS_TAG, V2::DIALOG_ETS_TAG,
        V2::POPUP_ETS_TAG, V2::TOAST_ETS_TAG, V2::SELECT_ETS_TAG, V2::CHECK_BOX_ETS_TAG, V2::CHECKBOXGROUP_ETS_TAG,
        V2::SLIDER_ETS_TAG, V2::RATING_ETS_TAG, V2::RADIO_ETS_TAG, V2::SWITCH_ETS_TAG, V2::SWIPER_ETS_TAG,
        V2::SWIPER_INDICATOR_ETS_TAG, V2::SWIPER_LEFT_ARROW_ETS_TAG, V2::SWIPER_RIGHT_ARROW_ETS_TAG,
        V2::SWIPER_LEFT_CAPTURE_ETS_TAG, V2::SWIPER_RIGHT_CAPTURE_ETS_TAG, V2::INDICATOR_ETS_TAG };

    if (auto search = supportTags.find(tag); search != supportTags.end()) {
        return;
    }
    LOGF_ABORT("Unsupported UI components '%{public}s' used in ParallelizeUI", tag.c_str());
}
} // namespace OHOS::Ace