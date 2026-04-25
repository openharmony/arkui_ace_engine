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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H

#include "core/components_ng/base/frame_node.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include <mutex>
#include <shared_mutex>
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "interfaces/inner_api/ace/viewport_config.h"
#include "interfaces/inner_api/ace_kit/include/ui/common/window_animation_config.h"

namespace OHOS::Rosen {
class OccupiedAreaChangeInfo;
class AvoidArea;
enum class AvoidAreaType : uint32_t;
enum class OccupiedAreaType : uint32_t;
enum class WindowSizeChangeReason : uint32_t;
} // namespace OHOS::Rosen
#endif

namespace OHOS::Ace::NG {
class PlatformPattern;
struct AvoidRect {
    int32_t posX_ = 0;
    int32_t posY_ = 0;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

class AvoidArea : public AceType {
    DECLARE_ACE_TYPE(AvoidArea, AceType);
public:
    AvoidRect topRect_ { 0, 0, 0, 0 };
    AvoidRect leftRect_ { 0, 0, 0, 0 };
    AvoidRect rightRect_ { 0, 0, 0, 0 };
    AvoidRect bottomRect_ { 0, 0, 0, 0 };
};

enum class OccupiedAreaType : uint32_t {
    TYPE_INPUT, // area of input window
};

class OccupiedAreaChangeInfo : public AceType {
public:
    OccupiedAreaType type_ = OccupiedAreaType::TYPE_INPUT;
    AvoidRect rect_ = { 0, 0, 0, 0 };
    uint32_t safeHeight_ = 0;
    double textFieldPositionY_ = 0.0;
    double textFieldHeight_ = 0.0;
};

class DynamicComponentSafeManager : public AceType {
    DECLARE_ACE_TYPE(DynamicComponentSafeManager, AceType);
#ifdef WINDOW_SCENE_SUPPORTED
public:
    void SetAvoidArea(const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas);
    void SetOccupiedAreaChangeInfo(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info);
    sptr<OHOS::Rosen::OccupiedAreaChangeInfo> GetOccupiedAreaChangeInfo() const;
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> GetAvoidArea() const;
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> GetFaultAvoidArea() const;
    void UpdateAllDCAvoidArea(int32_t instanceId, const OHOS::Rosen::AvoidArea avoidArea,
        OHOS::Rosen::AvoidAreaType type);
    bool UpdateDynamicKeyBoardAvoid(const RefPtr<PipelineBase>& pipelineContext,
        OHOS::Rosen::WindowSizeChangeReason reason,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas);
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> GetAvoidAreaIntersection(
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
        OHOS::Ace::ViewportConfig viewportConfig);

    mutable std::shared_mutex avoidAreasMutex_;
    std::map<int32_t, OHOS::Ace::WeakPtr<PlatformPattern>> aliveDynamics_;
    OHOS::Ace::ViewportConfig viewportConfig_;
    OHOS::Ace::WindowSizeChangeReason reason_;
    std::shared_ptr<OHOS::Rosen::RSTransaction> rsTransaction_;
    RefPtr<OccupiedAreaChangeInfo> occupiedAreaChangeInfo_;
    std::map<OHOS::Rosen::AvoidAreaType, RefPtr<AvoidArea>> avoidAreas_;
#endif
};

class ACE_EXPORT DynamicComponentManager {
public:
    DynamicComponentManager() {}
    ~DynamicComponentManager() {};
    static void TriggerOnAreaChangeCallback(
        FrameNode* frameNode, uint64_t nanoTimestamp, int32_t areaChangeMinDepth = -1);
    static void HandleDynamicRenderOnAreaChange(FrameNode* frameNode, const RectF& currFrameRect,
        const OffsetF& currParentOffset, const OffsetF& currHostParentOffset);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H
