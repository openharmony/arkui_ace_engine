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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_LOADER_H

#include <functional>
#include <memory>

#include "interfaces/inner_api/ace/share/text_share_interface.h"

namespace OHOS::Ace {
using TextShareInstance = std::unique_ptr<TextShareInterface,
    std::function<void (TextShareInterface*)>>;

class TextShareLoader : public std::enable_shared_from_this<TextShareLoader> {
public:
    static std::shared_ptr<TextShareLoader> Load();
    ~TextShareLoader();
    TextShareLoader() = default;

    TextShareLoader(const TextShareLoader&) = delete;
    TextShareLoader(TextShareLoader&&) = delete;
    TextShareLoader& operator=(const TextShareLoader&) = delete;
    TextShareLoader& operator=(TextShareLoader&&) = delete;

    TextShareInstance CreateTextShare();

private:
    bool Init();
    void Close();

    void *mLibraryHandle_ = nullptr;
    TextShareInterface* (*mCreateTextShareInstance_)() = nullptr;
    void (*mDestoryTextShareInstance_)(TextShareInterface*) = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_LOADER_H
