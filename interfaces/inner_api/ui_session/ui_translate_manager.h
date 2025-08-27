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

#ifndef INTERFACE_INNERAPI_UI_SESSION_UI_TRANSLATE_MANAGER_H
#define INTERFACE_INNERAPI_UI_SESSION_UI_TRANSLATE_MANAGER_H
#include <cstdint>
#include <functional>
#include <vector>

#include "ui_session_json_util.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiTranslateManager {
public:
    virtual ~UiTranslateManager() = default;
    virtual void GetWebViewCurrentLanguage() {};
    virtual void GetTranslateText(std::string extraData, bool isContinued) {};
    virtual void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) {};
    virtual void SendTranslateResult(int32_t nodeId, std::string res) {};
    virtual void ResetTranslate(int32_t nodeId);
    virtual void ClearMap();
    virtual void PostToUI(const std::function<void()>& task) {};
};
} // namespace OHOS::Ace
#endif
