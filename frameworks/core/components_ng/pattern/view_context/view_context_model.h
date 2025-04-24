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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H

#include <mutex>

#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ViewContextModel {
public:
    static ViewContextModel* GetInstance();
    virtual ~ViewContextModel() = default;

    virtual void closeAnimation(const AnimationOption& option, bool needFlush) = 0;
    virtual void openAnimation(const AnimationOption& option) = 0;
    virtual int32_t OpenBindSheet(const RefPtr<NG::FrameNode>& bindContentNode,
        std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        int32_t currentInstanceId, int32_t targetId) = 0;
    virtual int32_t UpdateBindSheet(
        const RefPtr<NG::FrameNode>& bindContentNode, const NG::SheetStyle& sheetStyle, bool isPartialUpdate,
        int32_t currentInstanceId) = 0;
    virtual int32_t CloseBindSheet(const RefPtr<NG::FrameNode>& bindContentNode, int32_t currentInstanceId) = 0;

private:
    static std::unique_ptr<ViewContextModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIEW_VIEW_CONTEXT_MODEL_H
