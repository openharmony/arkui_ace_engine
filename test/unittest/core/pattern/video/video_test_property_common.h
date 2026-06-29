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

#ifndef VIDEO_TEST_PROPERTY_COMMON_H
#define VIDEO_TEST_PROPERTY_COMMON_H

#include <optional>
#include <string>

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/video/video_controller_v2.h"

namespace OHOS::Ace::NG {

// Single source of truth for TestProperty across every TU linked into video_test_ng.
// Do NOT duplicate this struct in individual .cpp files: divergent definitions are an
// ODR violation whose mismatched destructor crashes at exit teardown.
struct TestProperty {
    std::optional<std::string> src;
    std::optional<double> progressRate;
    std::optional<std::string> posterUrl;
    std::optional<bool> showFirstFrame;
    std::optional<bool> muted;
    std::optional<bool> autoPlay;
    std::optional<bool> controls;
    std::optional<bool> loop;
    std::optional<ImageFit> objectFit;
    std::optional<RefPtr<VideoControllerV2>> videoController;
};

} // namespace OHOS::Ace::NG

#endif // VIDEO_TEST_PROPERTY_COMMON_H
