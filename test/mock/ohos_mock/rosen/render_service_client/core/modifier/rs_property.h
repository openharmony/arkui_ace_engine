/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>

#ifndef RENDER_SERVICE_CLIENT_CORE_MODIFIER_RS_PROPERTY_H
#define RENDER_SERVICE_CLIENT_CORE_MODIFIER_RS_PROPERTY_H
namespace OHOS {
namespace Rosen {
enum class ThresholdType {
    /** 0.5f for properties like position, as the difference in properties by 0.5 appears visually unchanged. */
    LAYOUT = 0,
    /** 1.0f / 256.0f */
    COARSE,
    /** 1.0f / 1000.0f */
    MEDIUM,
    /** 1.0f / 3072.0f */
    FINE,
    /** 0.0f */
    COLOR,
    /** 1.0f / 256.0f */
    DEFAULT,
    /** 0.0f for noanimatable property */
    ZERO,
};

class RSPropertyBase : public std::enable_shared_from_this<RSPropertyBase> {
public:
    RSPropertyBase() =default;
    virtual ~RSPropertyBase() = default;
    virtual void SetThresholdType(ThresholdType thresholdType) {}
};
}
}
#endif
