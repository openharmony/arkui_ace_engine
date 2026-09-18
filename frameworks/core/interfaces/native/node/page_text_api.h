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
#ifndef ARKUI_PAGE_TEXT_API_H
#define ARKUI_PAGE_TEXT_API_H
#include <cstdint>

// Separate versioned entry keeps the existing node API tables ABI-compatible.
struct ArkUIPageTextAPI {
    int32_t (*collect)(int32_t instanceId, char** data, uint32_t* size, const char** reason);
    void (*release)(char* data);
};
namespace OHOS::Ace::NodeModel {
const ArkUIPageTextAPI* GetPageTextAPI();
}
#endif
