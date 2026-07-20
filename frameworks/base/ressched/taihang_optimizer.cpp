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
#include "taihang_optimizer.h"
#include "ressched_report.h"

#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/thread/background_task_executor.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t SWIPER = 1;
} // namespace

void TaihangOptimizer::Init()
{
    CHECK_EQUAL_VOID(isInited_, true);
    isInited_ = true;
    std::weak_ptr<TaihangOptimizer> weakThis = shared_from_this();
    auto task = [weakThis]() {
        auto optimizerRef = weakThis.lock();
        CHECK_NULL_VOID(optimizerRef);
        std::unordered_map<std::string, std::string> payload;
        std::unordered_map<std::string, std::string> reply;
        auto swiperReportEnable = ResSchedReport::GetInstance().AppSwiperReportEnableCheck(payload, reply);
        if (swiperReportEnable) {
            std::unique_lock<std::shared_mutex> lock(optimizerRef->processWhiteListMutex_);
            optimizerRef->ParseReplyPages(reply);
        }
        optimizerRef->SetEnable(swiperReportEnable);
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "TaihangOptimizer::Init swiper report enable : %{public}d",
            static_cast<int32_t>(optimizerRef->enable_));
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
}

bool TaihangOptimizer::IsInited()
{
    return isInited_;
}

bool TaihangOptimizer::IsEnable()
{
    return enable_;
}

void TaihangOptimizer::SetEnable(bool value)
{
    enable_ = value;
}

void TaihangOptimizer::ParseReplyPages(const std::unordered_map<std::string, std::string>& reply)
{
    CHECK_EQUAL_VOID(reply.empty(), true);
    auto pageIter = reply.find("pageNames");
    CHECK_EQUAL_VOID(pageIter, reply.end());
    std::string pages = pageIter->second;
    auto jsonObj = JsonUtil::ParseJsonString(pages);
    CHECK_EQUAL_VOID(jsonObj, nullptr);
    if (!jsonObj->IsArray()) {
        return;
    }
    int32_t size = jsonObj->GetArraySize();
    for (int i = 0; i < size; i++) {
        auto nameJson = jsonObj->GetArrayItem(i);
        if (nameJson && nameJson->IsString()) {
            auto name = nameJson->GetString();
            pageNameSet_.insert(name);
        }
    }
}

bool TaihangOptimizer::CheckSwiperPageValid(const std::string& pageName)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER, "TaihangOptimizer::CheckSwiperPageValid pageName: %{public}s", pageName.c_str());
    CHECK_EQUAL_RETURN(isInited_, false, false);
    CHECK_EQUAL_RETURN(enable_, false, false);
    std::shared_lock<std::shared_mutex> lock(processWhiteListMutex_);
    CHECK_EQUAL_RETURN(pageNameSet_.empty(), true, false);
    std::vector<std::string> pageNames;
    StringUtils::StringSplitter(pageName, ',', pageNames);
    for (auto pageName : pageNames) {
        if (pageNameSet_.find(pageName) != pageNameSet_.end()) {
            return true;
        }
    }
    return false;
}

void TaihangOptimizer::ComponentPreMake(const std::unordered_map<std::string, std::string> extInfo)
{
    auto iter = extInfo.find("componentType");
    CHECK_EQUAL_VOID(iter, extInfo.end());
    auto componentType = StringUtils::StringToInt(iter->second);
    switch (componentType) {
        case SWIPER:
            HandleSwiperPreMake(extInfo);
            break;
        default:
            break;
    }
}

void TaihangOptimizer::HandleSwiperPreMake(const std::unordered_map<std::string, std::string> extInfo)
{
    ACE_SCOPED_TRACE("TaihangOptimizer::HandleSwiperPreMake");
    auto iter = extInfo.find("path");
    CHECK_EQUAL_VOID(iter, extInfo.end());
    std::string path = iter->second;
    auto indexIter = extInfo.find("index");
    CHECK_EQUAL_VOID(indexIter, extInfo.end());
    auto index = StringUtils::StringToInt(indexIter->second, -1);
    CHECK_EQUAL_VOID(index, -1);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto root = pipeline->GetRootElement();
    CHECK_NULL_VOID(root);
    int32_t idx = 0;
    std::vector<std::string> subComponents;
    StringUtils::StringSplitter(path, '/', subComponents);
    RefPtr<NG::UINode> curUINode = root;
    for (std::string curComponent: subComponents) {
        if (!curUINode) {
            break;
        }
        size_t start_pos = curComponent.find('[');
        if (start_pos == std::string::npos) {
            continue;
        }
        size_t end_pos = curComponent.find(']');
        if (end_pos == std::string::npos || end_pos <= start_pos + 1) {
            return;
        }
        std::string idxChar = curComponent.substr(start_pos + 1, end_pos - start_pos -1);
        idx = StringUtils::StringToInt(idxChar, -1);
        CHECK_EQUAL_VOID(idx, -1);
        curUINode = curUINode->GetChildAtIndex(idx);
    }
    if (curUINode && curUINode->GetTag() == V2::SWIPER_ETS_TAG) {
        TAG_LOGD(AceLogTag::ACE_SWIPER, "TaihangOptimizer::HandleSwiperPreMake node is exist, path %{public}s",
            curUINode->GetPath().c_str());
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(curUINode);
        PostSwiperPreMakeTask(frameNode, index);
    } else {
        TAG_LOGW(AceLogTag::ACE_SWIPER, "TaihangOptimizer::HandleSwiperPreMake node is not exist");
    }
}

void TaihangOptimizer::PostSwiperPreMakeTask(RefPtr<NG::FrameNode>& node, int32_t index)
{
    CHECK_NULL_VOID(node);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskExecutor->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(node)), index]() {
            auto curNode = weak.Upgrade();
            CHECK_NULL_VOID(curNode);
            auto swiperPattern = curNode->GetPattern<NG::SwiperPattern>();
            CHECK_NULL_VOID(swiperPattern);
            auto swiperController = swiperPattern->GetSwiperController();
            CHECK_NULL_VOID(swiperController);
            swiperController->PreMakeItems({index});
        },
        TaskExecutor::TaskType::UI, "ArkUIPreMakeThirdApp");
}
} // namespace OHOS::Ace
