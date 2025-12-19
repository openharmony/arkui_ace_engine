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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_CREATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_CREATOR_H

#include <functional>

namespace OHOS::Ace {
template<class T>
class RefPtr;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class RenderContext;
using RenderContextCreateFunction = std::function<RefPtr<RenderContext>(void)>;
class MockRenderContextCreator {
public:
    static void SetRenderContextCreateFunction(RenderContextCreateFunction&& func)
    {
        renderContextCreateFunc_ = std::move(func);
    }
    static void ResetRenderContextCreateFunction()
    {
        renderContextCreateFunc_ = nullptr;
    }
    static thread_local RenderContextCreateFunction renderContextCreateFunc_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_CREATOR_H
