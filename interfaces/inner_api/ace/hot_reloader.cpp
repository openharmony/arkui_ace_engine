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

#include "interfaces/inner_api/ace/hot_reloader.h"

#include "utils.h"
#include "ace_forward_compatibility.h"

namespace OHOS::Ace {

using ReloadFunc = void (*)();
constexpr char HOT_RELOAD_FUNC[] = "OHOS_ACE_HotReloadPage";

void InitAceModule()
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<ReloadFunc>(LOADSYM(handle, HOT_RELOAD_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry();
}

void HotReloader::HotReload()
{
    InitAceModule();
}

} // namespace OHOS::Ace
