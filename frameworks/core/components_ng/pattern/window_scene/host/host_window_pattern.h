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

#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class HostWindowPattern : public Pattern {
    DECLARE_ACE_TYPE(HostWindowPattern, Pattern);

public:
    HostWindowPattern(const std::shared_ptr<Rosen::Session>& session) : session_(session) {}
    ~HostWindowPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    std::shared_ptr<Rosen::Session> GetSession()
    {
        return session_;
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

protected:
    virtual void InitContent();

    virtual void OnBackground();

    RefPtr<FrameNode> startingNode_;
    RefPtr<FrameNode> contentNode_;

private:
    std::shared_ptr<Rosen::Session> session_;

    friend class HostWindowSceneModel;

    ACE_DISALLOW_COPY_AND_MOVE(HostWindowPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOST_WINDOW_PATTERN_H
