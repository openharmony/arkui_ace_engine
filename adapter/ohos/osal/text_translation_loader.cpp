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

#include "core/common/ai/text_translation_loader.h"

#include <dlfcn.h>

#include "base/log/log_wrapper.h"

namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
constexpr char AI_TEXT_TRANS_SO_PATH[] = "system/lib64/libai_text_translation_innerapi.z.so";
#else
constexpr char AI_TEXT_TRANS_SO_PATH[] = "system/lib/libai_text_translation_innerapi.z.so";
#endif
} // namespace

// static
std::shared_ptr<TextTranslationLoader> TextTranslationLoader::Load()
{
    auto engLib(std::make_shared<TextTranslationLoader>());
    return engLib->Init() ? engLib : nullptr;
}

TextTranslationLoader::~TextTranslationLoader()
{
    Close();
}

bool TextTranslationLoader::Init()
{
    mLibraryHandle_ = dlopen(AI_TEXT_TRANS_SO_PATH, RTLD_LAZY);
    if (mLibraryHandle_ == nullptr) {
        return false;
    }
    mCreateTextTranslationInstance_ = (TextTranslationInterface* (*)())dlsym(mLibraryHandle_,
        "OHOS_ACE_createTextTranslationInstance");
    mDestoryTextTranslationInstance_ = (void (*)(TextTranslationInterface*))dlsym(
        mLibraryHandle_, "OHOS_ACE_destroyTextTranslationInstance");
    if (mCreateTextTranslationInstance_ == nullptr || mDestoryTextTranslationInstance_ == nullptr) {
        LOGE("Could not find engine interface function in %s", AI_TEXT_TRANS_SO_PATH);
        Close();
        return false;
    }
    return true;
}

TextTranslationInstance TextTranslationLoader::CreateTextTranslation()
{
    if (mCreateTextTranslationInstance_ == nullptr || mDestoryTextTranslationInstance_ == nullptr) {
        return TextTranslationInstance();
    }
    return TextTranslationInstance(mCreateTextTranslationInstance_(), [lib = shared_from_this(),
        destroy = mDestoryTextTranslationInstance_](TextTranslationInterface* e) {
            destroy(e);
        });
}

void TextTranslationLoader::Close()
{
    if (mLibraryHandle_ != nullptr) {
        dlclose(mLibraryHandle_);
    }
    mLibraryHandle_ = nullptr;
    mCreateTextTranslationInstance_ = nullptr;
    mDestoryTextTranslationInstance_ = nullptr;
}
} // namespace OHOS::Ace
