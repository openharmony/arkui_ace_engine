/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_RENDERING_CONTEXT_BASE_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_RENDERING_CONTEXT_BASE_H

#include "base/memory/referenced.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"

namespace OHOS::Ace::Framework {

class JSRenderingContextBase : public virtual AceType {
    DECLARE_ACE_TYPE(JSRenderingContextBase, AceType)
public:
    JSRenderingContextBase() = default;
    virtual ~JSRenderingContextBase() = default;

    virtual void SetAntiAlias() = 0;
    virtual void SetDensity() = 0;
    virtual void SetCanvasPattern(const RefPtr<AceType>& canvas) = 0;
    virtual void SetInstanceId(int32_t id) = 0;

    ACE_DISALLOW_COPY_AND_MOVE(JSRenderingContextBase);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_CANVAS_RENDERER_H
