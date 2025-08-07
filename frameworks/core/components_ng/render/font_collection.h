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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_FONT_COLLECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_FONT_COLLECTION_H

#include <functional>
#include <list>
#include <mutex>
#include <shared_mutex>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {
using LoadFontCallback = std::function<void(const std::string&)>;

class ACE_EXPORT FontCollection : public virtual AceType {
    DECLARE_ACE_TYPE(FontCollection, AceType)
public:
    static RefPtr<FontCollection> Current();

    const std::list<LoadFontCallback>& GetUnloadFontFinishCallback()
    {
        std::shared_lock lock(unloadLock_);
        return unloadFontFinishCallback_;
    }

    void RegisterUnloadFontFinishCallback(LoadFontCallback&& cb)
    {
        std::unique_lock lock(unloadLock_);
        unloadFontFinishCallback_.emplace_back(std::move(cb));
    }

    const std::list<LoadFontCallback>& GetLoadFontFinishCallback()
    {
        std::shared_lock lock(loadLock_);
        return loadFontFinishCallback_;
    }

    void RegisterLoadFontFinishCallback(LoadFontCallback&& cb)
    {
        std::unique_lock lock(loadLock_);
        loadFontFinishCallback_.emplace_back(std::move(cb));
    }

private:
    std::list<LoadFontCallback> unloadFontFinishCallback_;
    std::list<LoadFontCallback> loadFontFinishCallback_;
    std::shared_mutex mutable loadLock_;
    std::shared_mutex mutable unloadLock_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_FONT_COLLECTION_H
