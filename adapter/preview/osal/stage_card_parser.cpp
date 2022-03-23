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

#include "adapter/preview/osal/stage_card_parser.h"

namespace OHOS::Ace {

StageCardParser::StageCardParser() : manifestWindow_(Referenced::MakeRefPtr<Framework::ManifestWindow>())
{}

WindowConfig& StageCardParser::GetWindowConfig()
{
    return manifestWindow_->GetWindowConfig();
}

void StageCardParser::Parse(const std::string& contents, const std::string& selectUrl)
{
    auto rootJson = JsonUtil::ParseJsonString(contents);
    if (!rootJson || !rootJson->IsValid()) {
        LOGE("the form config is illegal");
        return;
    }
    std::unique_ptr<JsonValue> formConfig;
    auto formConfigs = rootJson->GetValue("forms");
    int32_t index = 0;
    if (formConfigs && formConfigs->IsArray()) {
        for (; index < formConfigs->GetArraySize(); ++index) {
            formConfig = formConfigs->GetArrayItem(index);
            if (formConfig && formConfig->Contains("src") && formConfig->GetString("src") == selectUrl) {
                break;
            }
        }
    }
    if (index == formConfigs->GetArraySize()) {
        LOGE("The configuration information for the url %{public}s does not exist", selectUrl.c_str());
        return;
    }
    colorMode_ = formConfig->GetString("colorMode");
    defaultDimension_ = formConfig->GetString("defaultDimension");
    description_ = formConfig->GetString("description");
    manifestWindow_->WindowParse(formConfig);
}

} // namespace OHOS::Ace::Framework
