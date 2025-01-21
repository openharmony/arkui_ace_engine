/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_BRIDGE_H

#include "base/want/want_wrap.h"
#include "core/components/common/properties/blur_style_option.h"

namespace OHOS::Ace::Framework {

class JSViewAbstractBridge {
public:
    static void GetBackgroundBlurStyleOption(napi_value value, BlurStyleOption& styleOption);
    static void GetBackgroundEffect(napi_value value, EffectOption& styleOption);
};
} // namespace OHOS::Ace::Framework
#endif // RAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_BRIDGE_H
