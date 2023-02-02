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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_PATTERN_H

#include "session/scene/host/include/session.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class HostWindowPattern : public Pattern {
    DECLARE_ACE_TYPE(HostWindowPattern, Pattern);

public:
    HostWindowPattern(const sptr<Rosen::Session>& session);
    ~HostWindowPattern() override = default;

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void OnModifyDone() override;

protected:
    void OnAttachToFrameNode() override;

    virtual void InitContent();

    virtual bool HasStartingPage() = 0;

    virtual void OnForeground() {}
    virtual void OnBackground() {}

    int32_t instanceId_ = -1;

    RefPtr<FrameNode> startingNode_;
    RefPtr<FrameNode> contentNode_;

    sptr<Rosen::Session> session_;

private:
    void BufferAvailableCallback();
    void OnClick();

    bool initialized_ = false;

    RefPtr<ClickEvent> clickListener_;

    friend class LifecycleListener;

    ACE_DISALLOW_COPY_AND_MOVE(HostWindowPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_PATTERN_H
