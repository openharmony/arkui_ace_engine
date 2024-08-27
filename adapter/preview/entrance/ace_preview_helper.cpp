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

#include "adapter/preview/entrance/ace_preview_helper.h"

#include <memory>
#include <mutex>

namespace OHOS::Ace::Platform {
namespace {
std::unique_ptr<AcePreviewHelper> instance_ = nullptr;
} // namespace
AcePreviewHelper* AcePreviewHelper::GetInstance()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        instance_.reset(new AcePreviewHelper());
    });
    return instance_.get();
}
} // namespace OHOS::Ace::Platform
