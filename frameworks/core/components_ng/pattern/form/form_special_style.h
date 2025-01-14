/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SPECIAL_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SPECIAL_STYLE_H

#include <cstdint>
#include "form_info.h"
namespace OHOS::Ace::NG {
enum class FormOperation : int32_t {
    KEEP,

    UNLOAD,

    LOAD,

    REFRESH
};

enum class FormStyleAttribution : int32_t {
    /* *
     * Normal
     */
    NORMAL,

    /* *
     * Parent control
     */
    PARENT_CONTROL,

    /* *
     * App lock.
     */
    APP_LOCK,
};
class FormSpecialStyle {
public:
    void SetIsForbiddenByParentControl(bool isForbiddenByParentControl);
    void SetIsLockedByAppLock(bool isLockedByAppLock);
    const char* GetResource();
    [[nodiscard]] FormStyleAttribution GetFormStyleAttribution() const;
    FormOperation GetOperationToNewFormStyle(const FormSpecialStyle& formSpecialStyle);
    bool IsNeedToShowSpecialStyle();
    bool IsLockedByAppLock() const;
    void SetInitDone();
    bool IsInited() const;
    void SetIsMultiAppForm(AppExecFwk::FormInfo &formInfo);
    bool IsMultiAppForm() const;
private:
    bool isForbiddenByParentControl_ = false;

    bool isLockedByAppLock_ = false;

    bool isInited_ = false;

    bool isMultiAppForm_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_SPECIAL_STYLE_H
