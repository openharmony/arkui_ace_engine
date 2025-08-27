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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_MODEL_H

#include <functional>
#include <mutex>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
enum class JsCounterResourceType {
    Height,
    Width,
    BackgroundColor
};
class ACE_FORCE_EXPORT CounterModel {
public:
    static CounterModel* GetInstance();
    virtual ~CounterModel() = default;

    using CounterEventFunc = std::function<void()>;

    virtual void Create() = 0;
    virtual void SetOnInc(CounterEventFunc&& onInc) = 0;
    virtual void SetOnDec(CounterEventFunc&& onDec) = 0;
    virtual void SetHeight(const Dimension& value) = 0;
    virtual void SetWidth(const Dimension& value) = 0;
    virtual void SetControlWidth(const Dimension& value) = 0;
    virtual void SetStateChange(bool value) = 0;
    virtual void SetBackgroundColor(const Color& value) = 0;
    virtual void SetEnableDec(bool enableDec) = 0;
    virtual void SetEnableInc(bool enableInc) = 0;
    virtual void CreateWithResourceObj(JsCounterResourceType resourceType, const RefPtr<ResourceObject>& resObj) = 0;

private:
    static std::unique_ptr<CounterModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_MODEL_H
