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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_TRANSLATION_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_TRANSLATION_LOADER_H

#include <functional>
#include <memory>
#include "interfaces/inner_api/ace/ai/text_translation_interface.h"

namespace OHOS::Ace {
using TextTranslationInstance = std::unique_ptr<TextTranslationInterface,
    std::function<void (TextTranslationInterface*)>>;

class TextTranslationLoader : public std::enable_shared_from_this<TextTranslationLoader> {
public:
    static std::shared_ptr<TextTranslationLoader> Load();
    ~TextTranslationLoader();
    TextTranslationLoader() = default;

    TextTranslationLoader(const TextTranslationLoader&) = delete;
    TextTranslationLoader(TextTranslationLoader&&) = delete;
    TextTranslationLoader& operator=(const TextTranslationLoader&) = delete;
    TextTranslationLoader& operator=(TextTranslationLoader&&) = delete;

    TextTranslationInstance CreateTextTranslation();

private:
    bool Init();
    void Close();

    void *mLibraryHandle_ = nullptr;
    TextTranslationInterface* (*mCreateTextTranslationInstance_)() = nullptr;
    void (*mDestoryTextTranslationInstance_)(TextTranslationInterface*) = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_TRANSLATION_LOADER_H
