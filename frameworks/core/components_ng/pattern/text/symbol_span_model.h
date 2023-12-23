/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {
class ACE_EXPORT SymbolSpanModel {
public:
    static SymbolSpanModel* GetInstance();
    virtual ~SymbolSpanModel() = default;

    virtual void Create(const uint32_t& unicode) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetFontColor(std::vector<Color>& symbolColor) = 0;
    virtual void SetSymbolRenderingStrategy(const uint32_t renderingStrategy) = 0;
    virtual void SetSymbolEffect(const uint32_t effectStrategy) = 0;

private:
    static std::unique_ptr<SymbolSpanModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_H
