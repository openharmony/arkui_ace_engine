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

#include "adapter/ohos/entrance/ui_content_tmp.h"
#include "adapter/ohos/entrance/ui_content_impl.h"

#include "ability_context.h"
#include "ability_info.h"
#include "configuration.h"
#include "dm/display_manager.h"
#include "init_data.h"
#include "ipc_skeleton.h"
#include "js_runtime_utils.h"
#include "native_reference.h"
#include "service_extension_context.h"

#include <dlfcn.h>
#include <vector>

namespace OHOS::Ace {

void* UIContentTmp::gContext = nullptr;
void* UIContentTmp::gRuntime = nullptr;

UIContentImpl* OHOS_ACE_CreateUIContentTmp(void* context, void* runtime)
{
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}


std::unique_ptr<UIContentTmp> UIContentTmp::CreateCard()
{
    std::unique_ptr<UIContentImpl> content;
    content.reset(OHOS_ACE_CreateUIContentTmp(UIContentTmp::gContext, UIContentTmp::gRuntime));
    return content;
}

} // namespace OHOS::Ace
