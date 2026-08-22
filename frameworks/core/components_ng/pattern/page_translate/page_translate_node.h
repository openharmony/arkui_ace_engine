/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PAGE_TRANSLATE_PAGE_TRANSLATE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PAGE_TRANSLATE_PAGE_TRANSLATE_NODE_H

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utf_helper.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT PageTranslateNode : public virtual AceType {
    DECLARE_ACE_TYPE(PageTranslateNode, AceType);

public:
    ~PageTranslateNode() override = default;

    virtual int32_t GetPageTranslateNodeId() const
    {
        return -1;
    }

    virtual std::string GetPageTranslateTextForReport() const
    {
        return "";
    }

    virtual bool ApplyPageTranslateResult(const std::string& /* result */, int64_t /* version */)
    {
        return false;
    }

    virtual void ResetPageTranslate() {}

    virtual std::string GetCurrentLanguage()
    {
        return "";
    }

    virtual void GetTranslateText(
        std::string /* extraData */, std::function<void(std::string)> /* callback */, bool /* isContinued */)
    {}

    virtual void SendTranslateResult(std::vector<std::string> /* results */, std::vector<int32_t> /* ids */) {}

    virtual void SendTranslateResult(std::string /* results */) {}

    virtual void EndTranslate() {}

protected:
    std::optional<std::u16string> pageTranslatedContent_;
    int64_t pageTranslateVersion_ = 0;
    std::u16string lastDrawnPageTranslateContent_;

    bool ApplyTranslateResultCommon(const std::string& result, int64_t version)
    {
        if (version < 0 || (pageTranslateVersion_ > 0 && version < pageTranslateVersion_)) {
            return false;
        }
        auto translatedText = UtfUtils::Str8ToStr16(result);
        if (translatedText.empty()) {
            return false;
        }
        if (pageTranslatedContent_.has_value() &&
            pageTranslatedContent_.value() == translatedText &&
            pageTranslateVersion_ == version) {
            return false;
        }
        pageTranslatedContent_ = std::move(translatedText);
        pageTranslateVersion_ = version;
        return true;
    }

    bool ResetTranslateCommon()
    {
        if (!pageTranslatedContent_.has_value() && pageTranslateVersion_ == 0) {
            return false;
        }
        pageTranslatedContent_.reset();
        pageTranslateVersion_ = 0;
        return true;
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PAGE_TRANSLATE_PAGE_TRANSLATE_NODE_H
