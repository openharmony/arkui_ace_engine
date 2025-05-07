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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_CONTEXT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_CONTEXT_MODEL_IMPL_H

#include "core/components_ng/pattern/view_context/view_context_model.h"

namespace OHOS::Ace::Framework {
class ViewContextModelImpl : public OHOS::Ace::ViewContextModel {
public:
    void openAnimation(const AnimationOption& option) override;
    void closeAnimation(const AnimationOption& option, bool needFlush) override;
    int32_t OpenBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode,
         std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        int32_t currentInstanceId, int32_t targetId) override { return 0; };
    int32_t UpdateBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode,
        const NG::SheetStyle& sheetStyle, bool isPartialUpdate, int32_t currentInstanceId) override { return 0; }
    int32_t CloseBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode,
        int32_t currentInstanceId) override { return 0; }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_CONTEXT_MODEL_IMPL_H
