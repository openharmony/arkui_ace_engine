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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H

#include "base/memory/ace_type.h"

class NativeEngine;
class NativeValue;

namespace OHOS::AAFwk {
class Want;
} // namespace AAFwk

namespace OHOS::Ace {
class ACE_EXPORT WantWrap : public AceType {
    DECLARE_ACE_TYPE(WantWrap, AceType)

public:
    static NativeValue* ConvertToNativeValue(const OHOS::AAFwk::Want& want, NativeEngine* engine);
    static RefPtr<WantWrap> CreateWantWrap(void* nativeEngine, void* nativeValue);

    virtual void SetWantParamsFromWantWrap(void* want) = 0;
    virtual std::string ToString() const = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H
