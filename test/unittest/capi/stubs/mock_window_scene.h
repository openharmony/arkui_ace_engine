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

#ifndef CAPI_STUBS_MOCK_WINDOW_SCENE_H
#define CAPI_STUBS_MOCK_WINDOW_SCENE_H

#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Rosen {
class ScreenSession : public virtual Ace::AceType {
    DECLARE_ACE_TYPE(ScreenSession, Ace::AceType);

public:
    ScreenSession(uint64_t screenId = 0) : id(screenId)
    {}

    uint64_t GetScreenId() const
    {
        return id;
    }

private:
    uint64_t id;
};

class ScreenSessionManagerClient {
public:
    static ScreenSessionManagerClient& GetInstance()
    {
        static ScreenSessionManagerClient instance;
        return instance;
    }

    Ace::RefPtr<ScreenSession> GetScreenSession(uint64_t screenId)
    {
        return Ace::AceType::MakeRefPtr<ScreenSession>(screenId);
    }
};
}

namespace OHOS::Ace::NG {
template<class T>
using sptr = RefPtr<T>;
class ACE_EXPORT ScreenNode : public FrameNode {
    DECLARE_ACE_TYPE(ScreenNode, FrameNode);

public:
    ScreenNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~ScreenNode() override = default;

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override;

    static RefPtr<ScreenNode> GetOrCreateScreenNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};

class ScreenPattern : public StackPattern {
    DECLARE_ACE_TYPE(ScreenPattern, StackPattern);

public:
    explicit ScreenPattern(const sptr<Rosen::ScreenSession>& screenSession)
    {
        SetScreenSession(screenSession);
    }
    ~ScreenPattern() override = default;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::EXTERNAL };
    }

    void SetScreenSession(const sptr<Rosen::ScreenSession>& screenSession);
    sptr<Rosen::ScreenSession> GetScreenSession()
    {
        return screenSession_;
    }
    uint32_t GetWindowPatternType() const override;

protected:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig) override;

private:
    float GetDensityInCurrentResolution();

    static float screenMaxWidth_;
    static float screenMaxHeight_;

    sptr<Rosen::ScreenSession> screenSession_;

    ACE_DISALLOW_COPY_AND_MOVE(ScreenPattern);
};
} // namespace OHOS::Ace::NG

#endif // CAPI_STUBS_MOCK_WINDOW_SCENE_H
