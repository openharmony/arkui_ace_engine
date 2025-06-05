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

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {
using LoadFontCallback = std::function<void(const std::string&)>;

class ACE_EXPORT FontCollection : public virtual AceType {
    DECLARE_ACE_TYPE(FontCollection, AceType)
public:
    static RefPtr<FontCollection> Current();

    const LoadFontCallback& GetUnloadFontFinishCallback()
    {
        return unloadFontFinishCallback_;
    }

    void RegisterUnloadFontFinishCallback(LoadFontCallback&& cb)
    {
        unloadFontFinishCallback_ = std::move(cb);
    }

    const LoadFontCallback& GetLoadFontFinishCallback()
    {
        return loadFontFinishCallback_;
    }

    void RegisterLoadFontFinishCallback(LoadFontCallback&& cb)
    {
        loadFontFinishCallback_ = std::move(cb);
    }

private:
    LoadFontCallback unloadFontFinishCallback_;
    LoadFontCallback loadFontFinishCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_FONT_COLLECTION_H
