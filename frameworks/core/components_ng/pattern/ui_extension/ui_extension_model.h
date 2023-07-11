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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_H

#include <memory>
#include <mutex>
#include <string>

#include "base/utils/macros.h"
#include "base/want/want_wrap.h"

namespace OHOS::AAFwk {
class Want;
class WantParams;
}

namespace OHOS::Ace {
namespace NG {
class UIExtensionProxy;
}
class ACE_EXPORT UIExtensionModel {
public:
    static UIExtensionModel* GetInstance();
    virtual ~UIExtensionModel() = default;

    virtual void Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    virtual void SetOnRemoteReady(std::function<void(const RefPtr<NG::UIExtensionProxy>&)>&& onRemoteReady);
    virtual void SetOnRelease(std::function<void(int32_t)>&& onRelease);
    virtual void SetOnResult(std::function<void(int32_t, const AAFwk::Want&)>&& onResult);
    virtual void SetOnReceive(std::function<void(const AAFwk::WantParams&)>&& onReceive);
    virtual void SetOnError(
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
private:
    static std::unique_ptr<UIExtensionModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_H
