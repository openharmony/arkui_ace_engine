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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/texttimer/texttimer_controller.h"

namespace OHOS::Ace {
enum class JsTextTimerResourceType {
    TEXTCOLOR,
    FONTWEIGHT,
    FONTSIZE,
    FONTFAMILY
};
class ACE_FORCE_EXPORT TextTimerModel {
public:
    static TextTimerModel* GetInstance();
    virtual ~TextTimerModel() = default;

    virtual RefPtr<TextTimerController> Create() = 0;
    virtual void SetFormat(const std::string& format) = 0;
    virtual void SetIsCountDown(bool isCountDown) = 0;
    virtual void SetInputCount(double count) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void SetItalicFontStyle(Ace::FontStyle value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetOnTimer(std::function<void(int64_t, int64_t)> &&onChange) = 0;
    virtual void SetTextShadow(const std::vector<Shadow>& value) = 0;
    virtual void CreateWithResourceObj(
        JsTextTimerResourceType jsResourceType, const RefPtr<ResourceObject>& resObj) = 0;

private:
    static std::unique_ptr<TextTimerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_H
