/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_FONT_COLLECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_FONT_COLLECTION_H

#include <mutex>

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/font_collection.h"
#else
#include "rosen_text/font_collection.h"
#endif

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/font_collection.h"
#ifdef USE_GRAPHIC_TEXT_GINE
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace::NG {

class ACE_EXPORT TxtFontCollection : public FontCollection {
    DECLARE_ACE_TYPE(TxtFontCollection, FontCollection)
public:
#ifndef USE_GRAPHIC_TEXT_GINE
    explicit TxtFontCollection(const std::shared_ptr<txt::FontCollection>& fontCollection);
#else
    explicit TxtFontCollection(const std::shared_ptr<RSFontCollection>& fontCollection);
#endif
    TxtFontCollection();
    ~TxtFontCollection() override = default;

    static RefPtr<FontCollection> GetInstance();

#ifndef USE_GRAPHIC_TEXT_GINE
    const std::shared_ptr<txt::FontCollection>& GetRawFontCollection()
#else
    const std::shared_ptr<RSFontCollection>& GetRawFontCollection()
#endif
    {
        return collection_;
    }

private:
#ifndef USE_GRAPHIC_TEXT_GINE
    std::shared_ptr<txt::FontCollection> collection_;
    sk_sp<txt::DynamicFontManager> dynamicFontManager_;
#else
    std::shared_ptr<RSFontCollection> collection_;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_FONT_COLLECTION_H
