/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_ROSEN_FONT_COLLECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_ROSEN_FONT_COLLECTION_H

#include <future>
#include <vector>
#include <unordered_set>

#include "rosen_text/font_collection.h"

#include "core/components/font/font_collection.h"

namespace OHOS::Ace {

class ACE_EXPORT RosenFontCollection : public FontCollection {
public:
    static RosenFontCollection& GetInstance();

    std::shared_ptr<Rosen::FontCollection> GetFontCollection() override;

    void LoadFontFromList(const uint8_t* fontData, size_t length, std::string familyName);

    void LoadFontFamily(const char* fontFamily, const char* familySrc);

    void VaryFontCollectionWithFontWeightScale(float fontWeightScale);

    void LoadSystemFont();

    void SetIsZawgyiMyanmar(bool isZawgyiMyanmar);

private:
    void LoadThemeFont(const char* fontFamily, std::unique_ptr<char[]> buffer, size_t size);

    void InitializeFontCollection();

    bool StdFilesystemExists(const std::string &path);

    std::shared_ptr<Rosen::FontCollection> fontCollection_;
    std::unordered_set<std::string> families_;

    std::string currentFamily_;

    bool isZawgyiMyanmar_ = false;
    std::once_flag fontFlag_;

    static RosenFontCollection instance;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_ROSEN_FONT_COLLECTION_H
