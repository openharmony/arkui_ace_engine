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
#include "core/components_ng/pattern/image/image_layout_property.h"

namespace OHOS::Ace {
namespace {
constexpr char DATA_IMAGE_PREFIX[] = "data:image";
constexpr int32_t DEFAULT_MAX_DEEP = 20;
constexpr int32_t DATA_IMAGE_PREFIX_LENGTH = 10;
constexpr int32_t DATA_IMAGE_LENGTH = 32;

bool SafeConvertStringToInt32(const std::string& str, int32_t& result)
{
    std::stringstream ss(str);
    ss >> result;
    return !ss.fail();
}

bool IsDataImageUrl(const std::string& url)
{
    return url.length() >= DATA_IMAGE_PREFIX_LENGTH &&
        url.compare(0, DATA_IMAGE_PREFIX_LENGTH, DATA_IMAGE_PREFIX) == 0;
}

std::string ProcessDataImageUrl(const std::string& dataUrl)
{
    std::string result = dataUrl.substr(0, DATA_IMAGE_LENGTH);
    std::replace(result.begin(), result.end(), ',', ';');
    return result;
}

std::string ProcessImageUrl(const std::string& url)
{
    if (IsDataImageUrl(url)) {
        return ProcessDataImageUrl(url);
    }
    return url;
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

void MergeNodeImageSource(const RefPtr<NG::FrameNode> node, std::string& imgSrc)
{
    CHECK_NULL_VOID(node);
    CHECK_NE_VOID(node->GetTag(), V2::IMAGE_ETS_TAG);

    auto imageLayoutProperty = node->GetLayoutProperty<NG::ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto info = imageLayoutProperty->GetImageSourceInfo();
    CHECK_NULL_VOID(info);

    MergeText(imgSrc, ProcessImageUrl(info->GetSrc()));
}
} // namespace

ResSchedClickOptimizer::ResSchedClickOptimizer()
{
    Init();
}

void ResSchedClickOptimizer::Init()
{
    SetMaxDeep(DEFAULT_MAX_DEEP);
    std::call_once(clickExtEnableFlag_, [this]() {
        auto task = [this]() {
            std::unordered_map<std::string, std::string> payload;
            std::unordered_map<std::string, std::string> reply;
            SetClickExtEnabled(ResSchedReport::GetInstance().AppClickExtEnableCheck(payload, reply));
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "CLICK_EXT_ENABLE_CHECK Result: %{public}d",
                static_cast<int32_t>(clickExtEnabled_));

            auto iter = reply.find("deep");
            CHECK_EQUAL_VOID(iter, reply.end());
            int32_t maxDeep = 0;
            bool res = SafeConvertStringToInt32(iter->second, maxDeep);
            CHECK_EQUAL_VOID(res, false);
            SetMaxDeep(maxDeep);
        };
        BackgroundTaskExecutor::GetInstance().PostTask(task);
    });
}

void ResSchedClickOptimizer::ReportClick(const WeakPtr<NG::FrameNode> weakNode, const GestureEvent& gestureEvent)
{
    if (!GetClickExtEnabled()) {
        ResSchedReport::GetInstance().ResSchedDataReport("click");
        return;
    }

    EventTarget target = gestureEvent.GetTarget();
    std::unordered_map<std::string, std::string> payload;
    payload["width"] = target.area.GetWidth().ToString();
    payload["height"] = target.area.GetHeight().ToString();
    payload["pid"] = std::to_string(AceApplicationInfo::GetInstance().GetPid());
    payload["uid"] = std::to_string(AceApplicationInfo::GetInstance().GetUid());
    payload["bundleName"] = AceApplicationInfo::GetInstance().GetPackageName();
    payload["abilityName"] = AceApplicationInfo::GetInstance().GetAbilityName();
    std::string text = "";
    std::string imgSrc = "";
    GetComponentTextAndImageSourceRecursive(weakNode, text, imgSrc, GetMaxDeep());
    CheckPayloadTextEmpty(weakNode, text);

    payload["text"] = text;
    payload["imgSrc"] = imgSrc;
    ResSchedReport::GetInstance().ResSchedDataReport("click", payload);
}

void ResSchedClickOptimizer::GetComponentTextAndImageSourceRecursive(
    const WeakPtr<NG::FrameNode> weakNode, std::string& text, std::string& imgSrc, const int32_t remain)
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
    MergeNodeImageSource(node, imgSrc);

    auto& children = node->GetFrameChildren();
    for (auto& childWeak : children) {
        GetComponentTextAndImageSourceRecursive(childWeak, text, imgSrc, remain - 1);
    }
}
} // namespace OHOS::Ace