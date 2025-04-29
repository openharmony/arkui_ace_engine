/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STYLES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STYLES_H

#include "core/components_ng/property/property.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
struct VideoSourceInfo {
    std::string src_;
    std::string bundleName_ = "";
    std::string moduleName_ = "";
    bool operator==(const VideoSourceInfo& videoSrcInfo) const
    {
        return src_ == videoSrcInfo.src_ && bundleName_ == videoSrcInfo.bundleName_ &&
            moduleName_ == videoSrcInfo.moduleName_;
    }
    bool operator!=(const VideoSourceInfo& videoSrcInfo) const
    {
        return !operator==(videoSrcInfo);
    }
};

struct VideoStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(VideoSource, VideoSourceInfo);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(PosterImageInfo, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Controls, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ObjectFit, ImageFit);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(VideoSize, SizeF);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STYLES_H
