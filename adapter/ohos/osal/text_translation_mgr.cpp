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

#include "core/common/ai/text_translation_mgr.h"

#include "core/common/ai/text_translation_default.h"

namespace OHOS::Ace {

TextTranslationMgr& TextTranslationMgr::GetInstance()
{
    static TextTranslationMgr instance;
    return instance;
}

TextTranslationMgr::TextTranslationMgr()
{
    auto lib = TextTranslationLoader::Load();
    if (lib == nullptr || (engine_ = lib->CreateTextTranslation()) == nullptr) {
        textTranslationIsSupported = false;
        engine_ = TextTranslationInstance(new TextTranslationDefault, [](TextTranslationInterface* e) {
            auto* p = reinterpret_cast<TextTranslationDefault*>(e);
            delete p;
        });
    } else {
        textTranslationIsSupported = true;
    }
}

int32_t TextTranslationMgr::PullUpTranslationPanel(std::string translateText, std::string rectStr)
{
    int32_t ret = -1;
    if (!textTranslationIsSupported) {
        return ret;
    }
    if (engine_) {
        ret = engine_->PullUpTranslationPanel(translateText, rectStr);
    }
    return ret;
}

} // namespace OHOS::Ace
