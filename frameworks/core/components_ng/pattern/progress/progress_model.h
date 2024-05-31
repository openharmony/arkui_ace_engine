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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ProgressModel {
public:
    static ProgressModel* GetInstance();
    virtual ~ProgressModel() = default;

    virtual void Create(double min, double value, double cachedValue, double max, NG::ProgressType type) = 0;
    virtual void SetValue(double value) = 0;
    virtual void SetColor(const Color& value) = 0;
    virtual void SetBackgroundColor(const Color& value) = 0;
    virtual void SetStrokeWidth(const Dimension& value) = 0;
    virtual void SetScaleCount(int32_t value) = 0;
    virtual void SetScaleWidth(const Dimension& value) = 0;
    virtual void SetBorderColor(const Color& value) = 0;
    virtual void SetBorderWidth(const Dimension& value) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontColor(const Color& value) = 0;
    virtual void SetText(const std::optional<std::string>& value) = 0;
    virtual void SetItalicFontStyle(const Ace::FontStyle& value) = 0;
    virtual void SetFontWeight(const FontWeight& value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetSweepingEffect(bool value) = 0;
    virtual void SetGradientColor(const NG::Gradient& value) = 0;
    virtual void SetPaintShadow(bool value) = 0;
    virtual void SetProgressStatus(NG::ProgressStatus value) = 0;
    virtual void SetShowText(bool value) = 0;
    virtual void SetRingSweepingEffect(bool value) = 0;
    virtual void SetLinearSweepingEffect(bool value) = 0;
    virtual void SetSmoothEffect(bool value) = 0;
    virtual void SetStrokeRadius(const Dimension& value) {}
    virtual void ResetStrokeRadius() {}

private:
    static std::unique_ptr<ProgressModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_H
