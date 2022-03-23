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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_CARD_PARSER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_CARD_PARSER_H

#include <string>

#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "frameworks/base/json/json_util.h"
#include "frameworks/bridge/common/manifest/manifest_window.h"

namespace OHOS::Ace {

class StageCardParser : public Referenced {
public:
    StageCardParser();
    ~StageCardParser() override = default;
    void Parse(const std::string& contents, const std::string& selectUrl);
    WindowConfig& GetWindowConfig();

private:
    std::string colorMode_;
    std::string defaultDimension_;
    std::string description_;
    RefPtr<Framework::ManifestWindow> manifestWindow_;
    ACE_DISALLOW_COPY_AND_MOVE(StageCardParser);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_CARD_PARSER_H
