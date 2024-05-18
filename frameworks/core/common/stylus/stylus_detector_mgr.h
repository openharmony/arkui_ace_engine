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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_MGR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_MGR_H

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "interfaces/inner_api/ace/stylus/stylus_detector_interface.h"
#include "stylus_detector_loader.h"

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace {
struct Hash {
    size_t operator()(const RefPtr<NG::FrameNode>& node) const
    {
        return node->GetId();
    }
};
using FrameNodeSet = std::unordered_set<RefPtr<NG::FrameNode>, Hash>;

class ACE_EXPORT StylusDetectorMgr final : public StylusDetectorInterface {
public:
    static StylusDetectorMgr* GetInstance();

    bool IsEnable() override;
    bool RegisterStylusInteractionListener(const std::shared_ptr<IStylusDetectorCallback>& callback) override;
    void UnRegisterStylusInteractionListener() override;
    bool Notify(const NotifyInfo& notifyInfo) override;

    bool IsNeedInterceptedTouchEvent(const TouchEvent& touchEvent);

    void AddTextFieldFrameNode(const RefPtr<NG::FrameNode>& textFieldNode);
    void RemoveTextFieldFrameNode(const int32_t id);

    int32_t GetDefaultNodeId() const
    {
        return nodeId_;
    }

private:
    StylusDetectorMgr();
    ~StylusDetectorMgr() = default;

    class StylusDetectorCallBack : public OHOS::Ace::IStylusDetectorCallback {
    public:
        explicit StylusDetectorCallBack() = default;
        virtual ~StylusDetectorCallBack() = default;
        static void RequestFocus(int32_t nodeId);
        static void SetText(int32_t nodeId, std::string args);
        static std::string GetText(int32_t nodeId);

        void OnDetector(const CommandType& command, std::string args,
            std::shared_ptr<IAceStylusCallback> callback) override;

    };

    bool IsStylusTouchEvent(const TouchEvent& touchEvent) const;

    RefPtr<NG::FrameNode> FindTextInputFrameNodeByPosition(float globalX, float globalY);

    RefPtr<NG::FrameNode> FindTargetInChildNodes(
        const RefPtr<NG::UINode> parentNode, const FrameNodeSet& hitFrameNodes);

    bool CheckTextEditable(const RefPtr<NG::FrameNode> parentNode);

    std::unordered_map<int32_t, WeakPtr<NG::FrameNode>> textFieldNodes_;

    StylusDetectorInstance engine_ = nullptr;
    bool isRegistered_ = false;
    int32_t nodeId_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_MGR_H