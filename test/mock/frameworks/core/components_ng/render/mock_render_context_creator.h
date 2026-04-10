/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MOCK_RENDER_CONTEXT_CREATOR_H
#define FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MOCK_RENDER_CONTEXT_CREATOR_H

#include <functional>
#include <utility>

#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
using RenderContextCreateFunction = std::function<RefPtr<RenderContext>()>;

class MockRenderContextCreator {
public:
    static void SetRenderContextCreateFunc(RenderContextCreateFunction func)
    {
        renderContextCreateFunc_ = std::move(func);
    }

    static void Reset()
    {
        renderContextCreateFunc_ = nullptr;
    }

    inline static thread_local RenderContextCreateFunction renderContextCreateFunc_ = nullptr;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_MOCK_RENDER_CONTEXT_CREATOR_H
