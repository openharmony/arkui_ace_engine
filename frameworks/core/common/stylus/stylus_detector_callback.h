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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_CALLBACK_H

#include "interfaces/inner_api/ace/stylus/stylus_detector_interface.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace {
class StylusDetectorCallBack : public OHOS::Ace::IStylusDetectorCallback {
public:
    explicit StylusDetectorCallBack() = default;
    virtual ~StylusDetectorCallBack() = default;
    static int32_t RequestFocus(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler);
    static int32_t SetText(int32_t nodeId, void* data, const RefPtr<TaskExecutor>& taskScheduler,
        std::shared_ptr<IAceStylusCallback> callback);
    static int32_t GetText(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler,
        std::shared_ptr<IAceStylusCallback> callback);
    static int32_t DeleteText(int32_t nodeId, void* data, const RefPtr<TaskExecutor>& taskScheduler);
    static int32_t ChoiceText(int32_t nodeId, void* data, const RefPtr<TaskExecutor>& taskScheduler);
    static int32_t InsertSpace(int32_t nodeId, void* data, const RefPtr<TaskExecutor>& taskScheduler);
    static int32_t MoveCursor(int32_t nodeId, void* data, const RefPtr<TaskExecutor>& taskScheduler);

    static int32_t Redo(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler);
    static int32_t Undo(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler);
    int32_t OnDetector(
        const CommandType& command, void* data, std::shared_ptr<IAceStylusCallback> callback) override;
    bool OnDetectorSync(const CommandType& command) override;

private:
    static int32_t HandleMoveCursor(const RefPtr<NG::FrameNode>& frameNode, NG::PositionWithAffinity sInd,
        bool showHandle);
    static NG::PositionWithAffinity GetGlyphPositionByGlobalOffset(const RefPtr<NG::FrameNode>& frameNode,
        const Offset& offset);
    static std::tuple<int32_t, int32_t, int32_t> CalculateIntersectedRegion(NG::PositionWithAffinity sInd,
        NG::PositionWithAffinity eInd, int32_t wtextLength);
    static NG::OffsetF GetPaintRectGlobalOffset(const RefPtr<NG::FrameNode>& frameNode);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_CALLBACK_H