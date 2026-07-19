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
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

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
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PAGE_TRANSLATE_PAGE_TRANSLATE_NODE_H
