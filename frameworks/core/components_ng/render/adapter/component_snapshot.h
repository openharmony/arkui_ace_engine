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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H

#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/snapshot_param.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT ComponentSnapshot {
public:
    using JsCallback = std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>;
    using NormalCallback = std::function<void(std::shared_ptr<Media::PixelMap>)>;

    static void Get(const std::string& componentId, JsCallback&& callback, const SnapshotOptions& options);
    static void GetByUniqueId(int32_t uniqueId, JsCallback&& callback, const SnapshotOptions& options);
    // add delay to ensure Rosen has finished rendering
    static void Create(
        const RefPtr<AceType>& customNode, JsCallback&& callback, bool enableInspector, const SnapshotParam& param,
        bool flag = true);
    static void GetNormalCapture(const RefPtr<FrameNode>& frameNode, NormalCallback&& callback);

    static std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSync(const std::string& componentId,
        const SnapshotOptions& options);
    static std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetSyncByUniqueId(int32_t uniqueId,
        const SnapshotOptions& options);

    // create pixelMap in sync, this method only for drag.
    static std::shared_ptr<Media::PixelMap> CreateSync(
        const RefPtr<AceType>& customNode, const SnapshotParam& param);

private:
    static std::shared_ptr<Rosen::RSNode> GetRsNode(const RefPtr<FrameNode>& node);
    static void PostDelayedTaskOfBuiler(const RefPtr<TaskExecutor>& executor, JsCallback&& callback,
        const RefPtr<FrameNode>& node, bool enableInspector, const RefPtr<PipelineContext>& pipeline,
        const SnapshotParam& param);
    static void BuilerTask(JsCallback&& callback, const RefPtr<FrameNode>& node, bool enableInspector,
        const RefPtr<PipelineContext>& pipeline, const SnapshotParam& param);

    WeakPtr<FrameNode> node_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H