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
#include "core/common/ime/text_input_client.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"

namespace OHOS::Ace {
constexpr int32_t HOT_AREA_EXPAND_TIME = 2;
constexpr Dimension HOT_AREA_ADJUST_SIZE = 20.0_vp;
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
    bool RegisterStylusInteractionListener(
        const std::string& bundleName, const std::shared_ptr<IStylusDetectorCallback>& callback) override;
    void UnRegisterStylusInteractionListener(const std::string& bundleName) override;
    bool Notify(const NotifyInfo& notifyInfo) override;

    RefPtr<NG::FrameNode> FindHitFrameNode(const TouchEvent& touchEvent, const TouchTestResult& touchTestResult);
    bool IsNeedInterceptedTouchEvent(
        const TouchEvent& touchEvent, std::unordered_map<size_t, TouchTestResult> touchTestResults);

    void AddTextFieldFrameNode(const RefPtr<NG::FrameNode>& textFieldNode,
        const WeakPtr<NG::LayoutInfoInterface>& layoutInfo);
    void RemoveTextFieldFrameNode(const int32_t id);

    int32_t GetDefaultNodeId() const
    {
        return nodeId_;
    }

    WeakPtr<NG::LayoutInfoInterface> GetLayoutInfo() const
    {
        return layoutInfo_;
    }

    void SetSelectState(int32_t start, int32_t end, bool showMenu)
    {
        sInd_ = start;
        eInd_ = end;
        showMenu_ = showMenu;
    }

    bool HasSelectChanged(int32_t start, int32_t end, bool showMenu)
    {
        return (sInd_ != start || eInd_ != end || showMenu_ != showMenu);
    }
    

private:
    StylusDetectorMgr();
    ~StylusDetectorMgr() = default;

    bool IsStylusTouchEvent(const TouchEvent& touchEvent) const;
    bool IsHitCleanNodeResponseArea(
        const NG::PointF& point, const RefPtr<NG::FrameNode>& frameNode, uint64_t nanoTimestamp);

    std::unordered_map<int32_t, WeakPtr<NG::FrameNode>> textFieldNodes_;
    std::unordered_map<int32_t, WeakPtr<NG::LayoutInfoInterface>> textFieldLayoutInfos_;

    StylusDetectorInstance engine_ = nullptr;
    bool isRegistered_ = false;
    int32_t nodeId_ = 0;
    WeakPtr<NG::LayoutInfoInterface> layoutInfo_;
    int32_t sInd_ = -1;
    int32_t eInd_ = -1;
    bool showMenu_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_MGR_H