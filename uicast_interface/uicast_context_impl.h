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

#ifndef ACE_UICAST_IMPL_UICAST_CONTEXT_IMPL_H
#define ACE_UICAST_IMPL_UICAST_CONTEXT_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/dialog/dialog_properties.h"

#define RETURN_VOID_IF_NOT_ENABLE                    \
    if (!OHOS::Ace::UICastContextImpl::IsEnable()) { \
        return;                                      \
    }
#define RETURN_DEFAULT_IF_NOT_ENABLE                 \
    if (!OHOS::Ace::UICastContextImpl::IsEnable()) { \
        return 0;                                    \
    }

namespace OHOS::Ace {
class RenderNode;
class PipelineContext;

class ACE_EXPORT UICastContextImpl {
public:
    UICastContextImpl() = delete;
    static bool IsEnable();
    static void Init(const WeakPtr<PipelineContext>& context);
    static bool NeedsRebuild();
    static void OnFlushBuildStart();
    static void OnFlushBuildFinish();
    static bool CallRouterBackToPopPage();
    static void CheckEvent();
    static void HandleRouterPageCall(const std::string& cmd, const std::string& url);
    static void ShowToast(const std::string& message, int32_t duration, const std::string& bottom);
    static void ShowDialog(const DialogProperties& dialogProperties);

private:
    static int enable_;
};
} // namespace OHOS::Ace

#endif // ACE_UICAST_IMPL_UICAST_CONTEXT_IMPL_H