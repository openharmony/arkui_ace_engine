/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FONT_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FONT_LOADER_H

#include "base/memory/ace_type.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

class FontLoader : public virtual AceType {
    DECLARE_ACE_TYPE(FontLoader, AceType);

public:
    FontLoader(const std::string& familyName, const std::string& familySrc);
    FontLoader(const std::string& familyName, const std::vector<std::string>& familySrc);
    ~FontLoader() override = default;

    virtual void AddFont(const RefPtr<PipelineBase>& context, const std::string& bundleName = "",
        const std::string& moduleName = "") = 0;

    virtual void SetDefaultFontFamily(const char* fontFamily, const std::vector<std::string>& familySrc)
    {
        return;
    }

    static RefPtr<FontLoader> Create(const std::string& familyName, const std::string& familySrc);
    static RefPtr<FontLoader> CreateFontLoader(const char* familyName, const std::vector<std::string>& familySrc);

    const std::string& GetFamilyName() const;
    void SetOnLoaded(const WeakPtr<RenderNode>& node, const std::function<void()>& callback);
    void RemoveCallback(const WeakPtr<RenderNode>& node);
    void SetVariationChanged(const std::function<void()>& variationChanged);

    void SetOnLoadedNG(const WeakPtr<NG::UINode>& node, const std::function<void()>& callback);
    void RemoveCallbackNG(const WeakPtr<NG::UINode>& node);
    bool GetIsLoader() const
    {
        return isLoaded_;
    }

protected:
    std::string familyName_;
    std::string familySrc_;
    std::vector<std::string> familySrcArray_;
    std::map<WeakPtr<RenderNode>, std::function<void()>> callbacks_;
    std::map<WeakPtr<NG::UINode>, std::function<void()>> callbacksNG_;
    bool isLoaded_ = false;
    std::function<void()> variationChanged_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_FONT_LOADER_H
