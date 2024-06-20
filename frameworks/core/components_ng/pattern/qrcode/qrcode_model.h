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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_H

#include <mutex>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT QRCodeModel {
public:
    static QRCodeModel* GetInstance();
    virtual ~QRCodeModel() = default;
    virtual void Create(const std::string& value) = 0;
    virtual void SetQRCodeColor(const Color& color) = 0;
    virtual void SetQRBackgroundColor(const Color& color) = 0;
    virtual void SetContentOpacity(const double opacity) = 0;

private:
    static std::unique_ptr<QRCodeModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODEL_H