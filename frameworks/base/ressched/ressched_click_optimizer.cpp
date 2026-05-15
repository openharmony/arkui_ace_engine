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

#include "ressched_click_optimizer.h"
#include "ressched_report.h"

#include "base/thread/background_task_executor.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_UPDATE_TEXT_LENGTH = 1024;

bool SafeConvertStringToInt32(const std::string& str, int32_t& result)
{
    std::stringstream ss(str);
    ss >> result;
    return !ss.fail();
}

void GetPayloadPath(const WeakPtr<NG::FrameNode> weakNode, std::string& path)
{
    CHECK_EQUAL_VOID(path.empty(), false);
    auto node = weakNode.Upgrade();
    CHECK_NULL_VOID(node);
    path = node->GetPath();
}

void CheckPayloadTextEmpty(const WeakPtr<NG::FrameNode> weakNode, std::string& text)
{
    CHECK_EQUAL_VOID(text.empty(), false);
    auto node = weakNode.Upgrade();
    CHECK_NULL_VOID(node);
    auto property = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(property);

    text = property->GetGroupPreferAccessibilityText();
}

void MergeText(std::string& src, const std::string& target)
{
    if (!src.empty() && !target.empty()) {
        src += ",";
    }
    src += target;
}
} // namespace

void ResSchedClickOptimizer::Init()
{
    CHECK_EQUAL_VOID(isInit_, true);
    isInit_ = true;
    std::weak_ptr<ResSchedClickOptimizer> weakThis = shared_from_this();
    auto task = [weakThis]() {
        auto optimizerRef = weakThis.lock();
        CHECK_NULL_VOID(optimizerRef);

        std::unordered_map<std::string, std::string> payload;
        std::unordered_map<std::string, std::string> reply;
        optimizerRef->SetClickExtEnabled(ResSchedReport::GetInstance().AppClickExtEnableCheck(payload, reply));
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "CLICK_EXT_ENABLE_CHECK Result: %{public}d",
            static_cast<int32_t>(optimizerRef->clickExtEnabled_));

        auto iter = reply.find("depth");
        CHECK_EQUAL_VOID(iter, reply.end());
        int32_t depth = 0;
        bool res = SafeConvertStringToInt32(iter->second, depth);
        CHECK_EQUAL_VOID(res, false);
        optimizerRef->SetDepth(depth);
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
}

void ResSchedClickOptimizer::ReportClick(const WeakPtr<NG::FrameNode> weakNode, const GestureEvent& gestureEvent)
{
    if (!GetClickExtEnabled()) {
        ResSchedReport::GetInstance().ResSchedDataReport("click");
        return;
    }

    std::unordered_map<std::string, std::string> payload;
    payload["pid"] = std::to_string(AceApplicationInfo::GetInstance().GetPid());
    payload["uid"] = std::to_string(AceApplicationInfo::GetInstance().GetUid());
    payload["bundleName"] = AceApplicationInfo::GetInstance().GetPackageName();
    payload["abilityName"] = AceApplicationInfo::GetInstance().GetAbilityName();
    std::string text = "";
    std::string path = "";
    GetComponentTextRecursive(weakNode, text, GetDepth());
    CheckPayloadTextEmpty(weakNode, text);
    GetPayloadPath(weakNode, path);

    payload["path"] = path.substr(0, MAX_UPDATE_TEXT_LENGTH);
    payload["text"] = text.substr(0, MAX_UPDATE_TEXT_LENGTH);
    ResSchedReport::GetInstance().ResSchedDataReport("click", payload);
}

void ResSchedClickOptimizer::GetComponentTextRecursive(
    const WeakPtr<NG::FrameNode> weakNode, std::string& text, const int32_t remain)
{
    CHECK_EQUAL_VOID(remain <= 0, true);

    auto node = weakNode.Upgrade();
    CHECK_NULL_VOID(node);

    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);

    auto nodeText = accessibilityProperty->GetText();
    if (nodeText.empty()) {
        nodeText = accessibilityProperty->GetAccessibilityText();
    }

    MergeText(text, nodeText);

    auto& children = node->GetFrameChildren();
    for (auto& childWeak : children) {
        GetComponentTextRecursive(childWeak, text, remain - 1);
    }
}
} // namespace OHOS::Ace
