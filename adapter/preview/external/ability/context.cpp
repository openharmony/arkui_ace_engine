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

#include "adapter/preview/external/ability/context.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "adapter/preview/external/ability/fa/fa_context.h"
#include "adapter/preview/external/ability/stage/stage_context.h"

namespace OHOS::Ace {
namespace {
constexpr char MODULE_JSON[] = "module.json";
constexpr char CONFIG_JSON[] = "config.json";
#ifdef WINDOWS_PLATFORM
constexpr char DELIMITER[] = "\\";
#else
constexpr char DELIMITER[] = "/";
#endif
} // namespace

RefPtr<Context> Context::CreateContext(bool isStage, const std::string& rootDir)
{
    std::string filename = rootDir + DELIMITER + (isStage ? MODULE_JSON : CONFIG_JSON);
    std::string contents;
    std::ostringstream formatMessage;
    std::ifstream fin(filename, std::ios::in);
    if (!fin) {
        LOGW("Unable to open input file: %{public}s", filename.c_str());
        return nullptr;
    }
    while (fin >> contents) {
        formatMessage << contents;
    }
    contents = formatMessage.str();
    fin.close();
    RefPtr<Context> context;
    if (isStage) {
        context = AceType::MakeRefPtr<StageContext>();
    } else {
        context = AceType::MakeRefPtr<FaContext>();
    }
    context->Parse(contents);
    return context;
}
} // namespace OHOS::Ace
