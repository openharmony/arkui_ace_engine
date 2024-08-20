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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_CONTENT_ROOT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_CONTENT_ROOT_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/safe_area_insets.h"
namespace OHOS::Ace::NG {
class ContentRootPattern : virtual public Pattern {
    DECLARE_ACE_TYPE(ContentRootPattern, Pattern);

public:
    ContentRootPattern() = default;
    ~ContentRootPattern() override = default;

protected:
    // content roots need to apply SafeAreaInsets before layout
    void BeforeCreateLayoutWrapper() override;

    virtual bool AvoidKeyboard() const = 0;
    virtual bool AvoidTop() const = 0;
    virtual bool AvoidBottom() const = 0;
    virtual bool AvoidCutout() const = 0;

private:
    SafeAreaInsets CreateSafeAreaInsets() const;

    ACE_DISALLOW_COPY_AND_MOVE(ContentRootPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_CONTENT_ROOT_H
