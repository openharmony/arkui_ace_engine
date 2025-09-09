/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H

#include <cstdint>
#include <memory>
#include <vector>

namespace OHOS::Media {
class PixelMap;
} // namespace OHOS::Media

namespace OHOS::Ace {
void* CreateDrawableC(uint32_t type);
void* AnimatedGetController(void* object, const char* id);
int32_t AnimatedGetStatusC(void* object);
void* ParseResourceObject(void* object);
void GetPixelMapC(void* object, std::shared_ptr<Media::PixelMap>& pixelmap);
void AnimatedLoadSync(void* object, int32_t& width, int32_t& height, int32_t& errorCode);
void AnimatedSetPath(void* object, const char* path);
void AnimatedSetResource(void* object, void* resource);
void AnimatedSetPixelMapListC(void* object, std::vector<void*> pixelMaps);
void AnimatedSetTotalDurationC(void* object, int32_t duration);
void AnimatedSetDurationsC(void* object, const std::vector<int32_t>& durations);
void AnimatedSetIterationsC(void* object, int32_t iteration);
void AnimatedSetAutoPlayC(void* object, bool autoPlay);
void AnimatedStartC(void* object);
void AnimatedStopC(void* object);
void AnimatedPauseC(void* object);
void AnimatedResumeC(void* object);
void IncreaseRefCountDrawableC(void* object);
void DecreaseRefCountDrawableC(void* object);
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H