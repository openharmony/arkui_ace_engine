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

#include "base/json/json_util.h"

namespace OHOS::Ace {
std::unique_ptr<JsonValue> JsonUtil::ParseJsonData(const char* data, const char** parseEnd)
{
    (void)data;
    (void)parseEnd;
    return std::make_unique<JsonValue>(nullptr);
}

#if defined(ACE_STATIC)
std::unique_ptr<JsonValue> JsonUtil::ParseJsonDataWithLength(const char* data, size_t len)
{
    (void)data;
    (void)len;
    return std::make_unique<JsonValue>(nullptr);
}
#endif

std::unique_ptr<JsonValue> JsonUtil::ParseJsonString(const std::string& content, const char** parseEnd)
{
    (void)content;
    (void)parseEnd;
    return std::make_unique<JsonValue>(nullptr);
}

std::unique_ptr<JsonValue> JsonUtil::Create(bool isRoot)
{
    return std::make_unique<JsonValue>(nullptr, isRoot);
}

std::shared_ptr<JsonValue> JsonUtil::CreateSharedPtrJson(bool isRoot)
{
    return std::make_shared<JsonValue>(nullptr, isRoot);
}

std::unique_ptr<JsonValue> JsonUtil::CreateArray(bool isRoot)
{
    auto value = std::make_unique<JsonValue>(nullptr, isRoot);
    return value;
}
} // namespace OHOS::Ace
