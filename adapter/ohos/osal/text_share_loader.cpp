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
#include <dlfcn.h>

#include "base/log/log_wrapper.h"
#include "core/common/share/text_share_loader.h"

namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
constexpr char TEXT_SHARE_SO_PATH[] = "system/lib64/libsystemshare_innerkits.z.so";
#else
constexpr char TEXT_SHARE_SO_PATH[] = "system/lib/libsystemshare_innerkits.z.so";
#endif
} // namespace

// static
std::shared_ptr<TextShareLoader> TextShareLoader::Load()
{
    auto engLib(std::make_shared<TextShareLoader>());
    return engLib->Init() ? engLib : nullptr;
}

TextShareLoader::~TextShareLoader()
{
    Close();
}

bool TextShareLoader::Init()
{
    mLibraryHandle_ = dlopen(TEXT_SHARE_SO_PATH, RTLD_LAZY);
    if (mLibraryHandle_ == nullptr) {
        return false;
    }
    mCreateTextShareInstance_ = (TextShareInterface* (*)())dlsym(mLibraryHandle_,
        "OHOS_ACE_CreateTextShareInterface");
    mDestoryTextShareInstance_ = (void (*)(TextShareInterface*))dlsym(
        mLibraryHandle_, "OHOS_ACE_DestroyTextShareInterface");
    if (mCreateTextShareInstance_ == nullptr || mDestoryTextShareInstance_ == nullptr) {
        LOGE("Could not find engine interface function in %s", TEXT_SHARE_SO_PATH);
        Close();
        return false;
    }
    return true;
}

TextShareInstance TextShareLoader::CreateTextShare()
{
    if (mCreateTextShareInstance_ == nullptr || mDestoryTextShareInstance_ == nullptr) {
        return TextShareInstance();
    }
    return TextShareInstance(mCreateTextShareInstance_(), [lib = shared_from_this(),
        destroy = mDestoryTextShareInstance_](TextShareInterface* e) {
            destroy(e);
        });
}

void TextShareLoader::Close()
{
    if (mLibraryHandle_ != nullptr) {
        dlclose(mLibraryHandle_);
    }
    mLibraryHandle_ = nullptr;
    mCreateTextShareInstance_ = nullptr;
    mDestoryTextShareInstance_ = nullptr;
}
} // namespace OHOS::Ace