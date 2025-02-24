/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/manifest/manifest_window.h"

#include <regex>
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"

namespace OHOS::Ace::Framework {

void ManifestWindow::WindowParse(const std::unique_ptr<JsonValue>& root)
{
    if (!root) {
        LOGE("the root manifest is nullptr");
        return;
    }
    auto window = root->GetObject("window");
    if (!window || window->IsNull()) {
        return;
    }
    int32_t designWidth = 0;
    auto designWidthValue = window->GetValue("designWidth");
    if (designWidthValue->IsNumber()) {
        designWidth = designWidthValue->GetInt();
    } else if (designWidthValue->IsString()) {
        std::string designString = window->GetString("designWidth");
        std::regex reg("\\$(\\S+):(\\S+)");
        std::smatch results;

        auto resourceObject = AceType::MakeRefPtr<Ace::ResourceObject>("", "", Container::CurrentIdSafely());
        auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        if (std::regex_match(designString, results, reg) && resourceAdapter) {
            designWidth = resourceAdapter->GetInt(StringUtils::StringToInt(results[2].str()));
        }
    }
    if (designWidth <= 0) {
        LOGW("[designWidth] of [window] in main_pages.json set error. use default value: %{public}d",
            DEFAULT_DESIGN_WIDTH);
        designWidth = DEFAULT_DESIGN_WIDTH;
    }
    windowConfig_.designWidth = designWidth;
    windowConfig_.autoDesignWidth = window->GetBool("autoDesignWidth", false);
}

void ManifestWindow::PrintInfo() {}

} // namespace OHOS::Ace::Framework
