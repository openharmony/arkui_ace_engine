/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "core/common/share/text_share_mgr.h"

#include "core/common/share/text_share_default.h"

namespace OHOS::Ace {

TextShareMgr& TextShareMgr::GetInstance()
{
    static TextShareMgr instance;
    return instance;
}

TextShareMgr::TextShareMgr()
{
    auto lib = TextShareLoader::Load();
    if (lib == nullptr || (engine_ = lib->CreateTextShare()) == nullptr) {
        engine_ = TextShareInstance(new TextShareDefault, [](TextShareInterface* e) {
            auto* p = reinterpret_cast<TextShareDefault*>(e);
            delete p;
        });
    }
}

int32_t TextShareMgr::StartUpShareFunc(const std::shared_ptr<AbilityRuntime::Context>& context,
    const Rosen::Rect& anchorRect, const std::string& windowName, const std::string& textContent)
{
    if (engine_) {
        return engine_->StartUpShareFunc(context, anchorRect, windowName, textContent);
    }
    return -1;
}

uint64_t TextShareMgr::GetMaxTextLength()
{
    if (engine_) {
        return engine_->GetMaxTextLength();
    }
    return 0;
}
} // namespace OHOS::Ace