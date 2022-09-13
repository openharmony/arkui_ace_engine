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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/video/video_controller_v2.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_event_hub.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT VideoView {
public:
    static void Create(const RefPtr<VideoControllerV2>& videoController);
    static void SetSrc(const std::string& src);
    static void SetProgressRate(double progressRate);
    static void SetPosterSourceInfo(const std::string& posterUrl);
    static void SetMuted(bool muted);
    static void SetAutoPlay(bool autoPlay);
    static void SetControls(bool controls);
    static void SetObjectFit(ImageFit objectFit);
    static void SetLoop(bool loop);

    static void SetOnStart(EventCallback&& onStart);
    static void SetOnPause(EventCallback&& onPause);
    static void SetOnFinish(EventCallback&& onFinish);
    static void SetOnError(EventCallback&& onError);
    static void SetOnPrepared(EventCallback&& onPrepared);
    static void SetOnSeeking(EventCallback&& onSeeking);
    static void SetOnSeeked(EventCallback&& onSeeked);
    static void SetOnUpdate(EventCallback&& onUpdate);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_VIEW_H
