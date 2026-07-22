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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_GRADIENT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_GRADIENT_H

#include "ffi_remote_data.h"

#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeCanvasGradient : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeCanvasGradient, OHOS::FFI::FFIData)
public:
    explicit NativeCanvasGradient(const Gradient& gradient);
    ~NativeCanvasGradient() override;
    void AddColorStop(double offsetValue, const Color& colorValue);

    Gradient& GetGradient()
    {
        return gradient_;
    }

private:
    Gradient gradient_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_GRADIENT_H
