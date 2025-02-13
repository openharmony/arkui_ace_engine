
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

#include "core/components_ng/pattern/container_modal/container_modal_utils.h"

#include "bridge/common/utils/engine_helper.h"

extern const char _binary_customtitle_abc_start[];
extern const char _binary_customtitle_abc_end[];

namespace OHOS::Ace::NG {
bool ExecuteCustomTitleAbc()
{
    uint8_t* binaryBuff = nullptr;
    int32_t binarySize = 0;
    std::vector<uint8_t> buffer;

    auto filePath = "/system/etc/abc/arkui/customtitle.abc";
    // read abc file
    std::ifstream readFile(filePath, std::ifstream::binary);
    bool isLoadSuccess = false;
    if (readFile.is_open()) {
        readFile.seekg(0, std::ios::end);
        binarySize = static_cast<int32_t>(readFile.tellg());
        readFile.seekg(0, std::ios::beg);
        buffer.resize(binarySize);
        if (readFile.read((char*)buffer.data(), binarySize)) {
            TAG_LOGE(AceLogTag::ACE_APPBAR, "read abc file success!");
            binaryBuff = buffer.data();
            readFile.close();
            isLoadSuccess = true;
        } else {
            TAG_LOGE(AceLogTag::ACE_APPBAR, "open abc file failed!");
        }
    }
    if (!isLoadSuccess) {
        // use default abc file
        binaryBuff = (uint8_t*)_binary_customtitle_abc_start;
        binarySize = _binary_customtitle_abc_end - _binary_customtitle_abc_start;
    }
    // run abc file
    auto jsEngine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(jsEngine, false);
    if (!jsEngine->ExecuteJs(binaryBuff, binarySize)) {
        TAG_LOGE(AceLogTag::ACE_APPBAR, "execute abc file failed!");
        return false;
    }
    return true;
}

bool ExecuteCustomWindowMaskAbc()
{
    uint8_t* binaryBuff = nullptr;
    int32_t binarySize = 0;
    std::vector<uint8_t> buffer;

    auto filePath = "/system/etc/abc/arkui/windowmask.abc";
    // read abc file
    std::ifstream readFile(filePath, std::ifstream::binary);
    if (readFile && readFile.is_open()) {
        readFile.seekg(0, std::ios::end);
        binarySize = static_cast<int32_t>(readFile.tellg());
        readFile.seekg(0, std::ios::beg);
        buffer.resize(binarySize);
        if (readFile.read((char*)buffer.data(), binarySize)) {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "read windowmask abc file success!");
            binaryBuff = buffer.data();
            readFile.close();
        } else {
            TAG_LOGE(AceLogTag::ACE_APPBAR, "open windowmask abc file failed!");
            return false;
        }
    } else {
        TAG_LOGE(AceLogTag::ACE_APPBAR, "The abc file may not exist.");
        return false;
    }
    // run abc file
    auto jsEngine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(jsEngine, false);
    if (!jsEngine->ExecuteJs(binaryBuff, binarySize)) {
        TAG_LOGE(AceLogTag::ACE_APPBAR, "execute windowmask abc file failed!");
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG
