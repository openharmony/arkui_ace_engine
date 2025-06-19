/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#include "core/common/ai/data_detector_adapter.h"

namespace OHOS::Ace {
void DataDetectorAdapter::InitTextDetect(int32_t startPos, std::string detectText) {}
void DataDetectorAdapter::SetTextDetectTypes(const std::string& types)
{
    textDetectTypes_ = types;
}
bool DataDetectorAdapter::ParseOriText(const std::unique_ptr<JsonValue>& entityJson, std::u16string& text)
{
    return false;
}
void DataDetectorAdapter::ParseAIResult(const TextDataDetectResult& result, int32_t startPos) {}
void DataDetectorAdapter::ParseAIJson(
    const std::unique_ptr<JsonValue>& jsonValue, TextDataDetectType type, int32_t startPos) {}
void DataDetectorAdapter::StartAITask() {}

bool DataDetectorAdapter::ShowAIEntityMenu(
    const AISpan& aiSpan, const NG::RectF& aiRect, const RefPtr<NG::FrameNode>& targetNode, AIMenuInfo info)
{
    return true;
}

bool DataDetectorAdapter::GetAiEntityMenuOptions(const AISpan& aiSpan, const RefPtr<NG::FrameNode>& targetNode,
    AIMenuInfo info, std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
    const std::function<void()>& onMenuDisappear)
{
    return false;
}
RefPtr<NG::FrameNode> DataDetectorAdapter::CreateAIEntityMenu(const AISpan& aiSpan,
    const RefPtr<NG::FrameNode>& targetNode, AIMenuInfo info, const std::function<void()>& onMenuDisappear)
{
    return nullptr;
}

void DataDetectorAdapter::ResponseBestMatchItem(const AISpan& aiSpan) {}

void DataDetectorAdapter::OnClickAIMenuOption(const AISpan& aiSpan,
    const std::pair<std::string, FuncVariant>& menuOption, const RefPtr<NG::FrameNode>& targetNode,
    const std::function<void()>& onMenuDisappear, bool isFirst)
{}

void DataDetectorAdapter::GetAIEntityMenu() {}

std::function<void()> GetDetectDelayTask(const std::map<int32_t, AISpan>& aiSpanMap)
{
    return []() {};
}
} // namespace OHOS::Ace
