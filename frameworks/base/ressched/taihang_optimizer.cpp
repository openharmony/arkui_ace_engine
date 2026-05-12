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
constexpr int32_t DEFAULT_PAGENAME_SIZE = 2;
constexpr int32_t PREMAKE_SWIPER_DELAY_MILLISECONDS = 1000;
constexpr int32_t SWIPER = 1;

void GetReplyBundleNameAndPages(const std::unordered_map<std::string, std::string>& reply,
    std::unordered_map<std::string, std::vector<std::string>>& bundleNamePages)
{
    CHECK_EQUAL_VOID(reply.empty(), true);
    bundleNamePages.clear();
    for (auto it = reply.begin(); it != reply.end(); ++it) {
        std::string second = it->second;
        auto jsonObj = JsonUtil::ParseJsonString(second);
        if (!jsonObj || !jsonObj->IsValid()) {
            continue;
        }
        auto bundle = jsonObj->GetValue("bundleName");
        auto page = jsonObj->GetValue("pageName");
        if (!bundle || !page) {
            continue;
        }
        auto bundleName = bundle->GetString();
        auto pageName = page->GetString();
        if (bundleName.empty() || pageName.empty()) {
            continue;
        }
        auto iter = bundleNamePages.find(bundleName);
        if (iter != bundleNamePages.end()) {
            auto& pageNameList = iter->second;
            pageNameList.push_back(pageName);
        } else {
            std::vector<std::string> pageList;
            pageList.push_back(pageName);
            bundleNamePages.emplace(bundleName, pageList);
        }
    }
}
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
            GetReplyBundleNameAndPages(reply, optimizerRef->bundleNameToPages_);
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

bool TaihangOptimizer::CheckSwiperPathValid(const std::string& bundleName, const std::string& pageName)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER,
        "TaihangOptimizer::CheckSwiperPathValid bundleName = %{public}s, pageName = %{public}s",
        bundleName.c_str(), pageName.c_str());
    CHECK_EQUAL_RETURN(isInited_, false, false);
    CHECK_EQUAL_RETURN(enable_, false, false);
    std::shared_lock<std::shared_mutex> lock(processWhiteListMutex_);
    CHECK_EQUAL_RETURN(bundleNameToPages_.empty(), true, false);
    std::vector<std::string> pageNames;
    StringUtils::StringSplitter(pageName, ',', pageNames);
    if (pageNames.size() < DEFAULT_PAGENAME_SIZE) {
        return false;
    }
    auto it = bundleNameToPages_.find(bundleName);
    CHECK_EQUAL_RETURN(it, bundleNameToPages_.end(), false);
    auto pageNameList = it->second;
    for (const auto& curPageName: pageNameList) {
        if (curPageName == pageNames[1]) {
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
    std::string path = extInfo["path"];
    auto indexIter = extInfo.find("index");
    CHECK_EQUAL_VOID(indexIter, extInfo.end());
    auto index = StringUtils::StringToInt(indexIter->second);
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
    auto swiperPattern  =  node->GetPattern<NG::SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_VOID(swiperController);
    
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);

    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskExecutor->PostDelayedTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(swiperController)), index]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->PreMakeItems({index});
        },
        TaskExecutor::TaskType::UI, PREMAKE_SWIPER_DELAY_MILLISECONDS, "ArkUIPreMakeThirdApp");
}
} // namespace OHOS::Ace
