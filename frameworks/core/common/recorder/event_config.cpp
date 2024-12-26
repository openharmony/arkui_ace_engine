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
#include "core/common/recorder/event_config.h"
#include <cstdint>
#include <vector>

#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::Recorder {
EventConfig::EventConfig()
{
    switches_.resize(static_cast<int32_t>(EventCategory::CATEGORY_END), false);
    config_ = std::make_shared<Config>();
}

void EventConfig::Init(const std::string& config)
{
    auto jsonObj = JsonUtil::ParseJsonString(config);
    if (!jsonObj || !jsonObj->IsValid() || !jsonObj->IsObject()) {
        return;
    }
    ParseSwitch(jsonObj);
    ParseJsCode(jsonObj);
    auto cfgJsonArray = jsonObj->GetValue("config");
    if (!cfgJsonArray || !cfgJsonArray->IsArray()) {
        return;
    }
    for (int32_t i = 0; i < cfgJsonArray->GetArraySize(); ++i) {
        auto item = cfgJsonArray->GetArrayItem(i);
        if (!item || !item->IsObject()) {
            continue;
        }
        auto pageUrl = item->GetString("pageUrl");
        if (pageUrl.empty()) {
            continue;
        }
        PageCfg pageCfg;
        auto shareNodeArray = item->GetValue("shareNode");
        if (shareNodeArray && shareNodeArray->IsArray()) {
            ParseShareNode(shareNodeArray, pageCfg);
        }

        auto exposureCfgArray = item->GetValue("exposureCfg");
        if (exposureCfgArray && exposureCfgArray->IsArray()) {
            ParseExposureCfg(exposureCfgArray, pageCfg);
        }
        config_->emplace(std::move(pageUrl), std::move(pageCfg));
    }
}

void FillSwitch(std::vector<bool>& switches, const std::unique_ptr<JsonValue>& jsonObj)
{
    switches[static_cast<int32_t>(EventCategory::CATEGORY_PAGE)] = jsonObj->GetBool("page", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_COMPONENT)] = jsonObj->GetBool("component", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_EXPOSURE)] = jsonObj->GetBool("exposure", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_PAGE_PARAM)] = jsonObj->GetBool("pageParam", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_SCROLL)] = jsonObj->GetBool("scroll", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_ANIMATION)] = jsonObj->GetBool("animation", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_RECT)] = jsonObj->GetBool("rect", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_WEB)] = jsonObj->GetBool("web", false);
    switches[static_cast<int32_t>(EventCategory::CATEGORY_TEXT_INPUT)] = jsonObj->GetBool("textInput", false);
}

void EventConfig::ParseSwitch(const std::unique_ptr<JsonValue>& jsonObj)
{
    enable_ = jsonObj->GetBool("enable", false);
    auto switchVal = jsonObj->GetValue("switch");
    if (switchVal && switchVal->IsObject()) {
        FillSwitch(switches_, switchVal);
    }
    auto globalSwitchVal = jsonObj->GetValue("globalSwitch");
    if (globalSwitchVal && globalSwitchVal->IsObject()) {
        FillSwitch(EventRecorder::Get().globalSwitch_, globalSwitchVal);
    }
}

void EventConfig::ParseJsCode(const std::unique_ptr<JsonValue>& jsonObj)
{
    webCategory_ = jsonObj->GetString("webCategory");
    webIdentifier_ = jsonObj->GetString("webIdentifier");
    webJsCode_ = jsonObj->GetString("webActionJs");
}

void EventConfig::ParseShareNode(const std::unique_ptr<JsonValue>& shareNodeArray, PageCfg& pageCfg)
{
    for (int32_t j = 0; j < shareNodeArray->GetArraySize(); ++j) {
        auto shareNodeItem = shareNodeArray->GetArrayItem(j);
        if (!shareNodeItem || !shareNodeItem->IsString()) {
            continue;
        }
        auto id = shareNodeItem->GetString();
        if (id.empty()) {
            continue;
        }
        pageCfg.shareNodes.emplace_back(std::move(id));
    }
}

void EventConfig::ParseExposureCfg(const std::unique_ptr<JsonValue>& exposureCfgArray, PageCfg& pageCfg)
{
    for (int32_t j = 0; j < exposureCfgArray->GetArraySize(); ++j) {
        auto exposureCfgJson = exposureCfgArray->GetArrayItem(j);
        if (!exposureCfgJson || !exposureCfgJson->IsObject()) {
            continue;
        }
        auto id = exposureCfgJson->GetString("id");
        auto ratio = exposureCfgJson->GetDouble("ratio");
        auto duration = exposureCfgJson->GetInt("duration");
        if (id.empty() || duration <= 0) {
            continue;
        }
        ExposureCfg exposureCfg { std::move(id), ratio, duration };
        pageCfg.exposureCfgs.emplace_back(std::move(exposureCfg));
    }
}

bool EventConfig::IsEnable() const
{
    return enable_;
}

bool EventConfig::IsCategoryEnable(int32_t index) const
{
    if (index < 0 || index >= static_cast<int32_t>(switches_.size())) {
        return false;
    }
    return switches_[index];
}

const std::shared_ptr<Config>& EventConfig::GetConfig() const
{
    return config_;
}
} // namespace OHOS::Ace::Recorder
