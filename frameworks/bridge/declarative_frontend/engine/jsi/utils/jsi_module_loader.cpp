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

#include "frameworks/bridge/declarative_frontend/engine/jsi/utils/jsi_module_loader.h"

#include <cstdint>
#include <string>
#include <vector>

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/module_buffer_reader.h"
#include "core/common/container.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr size_t REQUIRE_UX_MODULE_PARAM = 2;
} // namespace

panda::Local<panda::JSValueRef> JsRequireHspModuleForAdvancedUIComponent(panda::JsiRuntimeCallInfo* info)
{
    auto* ecmaVM = info->GetVM();
    panda::EscapeLocalScope scope(ecmaVM);
    panda::Local<panda::JSValueRef> exports(panda::JSValueRef::Undefined(ecmaVM));
    if (info->GetArgsNumber() < REQUIRE_UX_MODULE_PARAM) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to require ex module, path or type is undefined");
        return scope.Escape(exports);
    }
    panda::Local<panda::StringRef> moduleRequestName(info->GetCallArgRef(0));
    if (moduleRequestName->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to require ex module, path is undefined");
        return scope.Escape(exports);
    }
    auto request = moduleRequestName->ToString(ecmaVM);

    panda::Local<panda::StringRef> keyValue(info->GetCallArgRef(1));
    if (keyValue->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to require ex module, key is undefined");
        return scope.Escape(exports);
    }
    auto key = keyValue->ToString(ecmaVM);

    uint8_t* data = nullptr;
    size_t dataSize = 0;
    if (!ModuleBufferReader::GetInstance().ReadModuleBuffer(request, &data, &dataSize)) {
        return scope.Escape(exports);
    }

    // LoadArkModule
    bool result = panda::JSNApi::ExecuteModuleBuffer(ecmaVM, data, static_cast<int32_t>(dataSize), request);
    if (!result) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "ExecuteModuleBuffer failed");
    } else {
        exports = panda::JSNApi::GetExportObject(ecmaVM, request, key);
        if (exports->IsUndefined()) {
            TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "get export object of %{private}s failed", key.c_str());
        }
    }
    if (panda::JSNApi::HasPendingException(ecmaVM)) {
        panda::JSNApi::PrintExceptionInfo(ecmaVM);
        panda::JSNApi::GetAndClearUncaughtException(ecmaVM);
    }
    return scope.Escape(exports);
}

} // namespace OHOS::Ace::Framework