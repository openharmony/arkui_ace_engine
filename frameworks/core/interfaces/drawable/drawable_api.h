/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_DRAWABLE_DRAWABLE_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_DRAWABLE_DRAWABLE_API_H

#ifdef __cplusplus
extern "C" {
#endif

#define DRAWABLE_FUNC_NAME "GetArkUIDrawableDescriptor"

struct ArkUIDrawableDescriptor {
    size_t (*getDrawableType)(void* object);
    void (*getPixelMap)(void* object, void* pixelMap);
    void (*setPixelRawData)(void* object, uint8_t* data, size_t len);
    void (*setForegroundData)(void* object, uint8_t* data, size_t len);
    void (*setBackgroundData)(void* object, uint8_t* data, size_t len);
    void (*setMaskData)(void* object, uint8_t* data, size_t len);
    void (*setMaskPath)(void* object, const char* path);
    void (*getForegroundPixelMap)(void* object, void* pixelMap);
    void (*getBackgroundPixelMap)(void* object, void* pixelMap);
    void (*getMaskPixelMap)(void* object, void* pixelMap);
    void (*getAnimatedPixelMaps)(void* object, void* pixelVec);
    int32_t (*getAnimatedDuration)(void* object);
    int32_t (*getAnimatedIterations)(void* object);
    void (*increaseRef)(void* object);
    void (*decreaseRef)(void* object);
    void* (*createDrawableDescriptorByType)(uint32_t type);
    void (*setPixelMapList)(void* object, void* pixelMapVec);
    void (*setAnimatedTotalDuration)(void* object, int32_t duration);
    void (*setAnimatedIterations)(void* object, int32_t iterations);
    void (*setAnimatedPath)(void* object, const char* path);
    void (*setAnimatedResource)(void* object, void* resourceObject);
    void (*setAnimatedAutoPlay)(void* object, bool autoPlay);
    void (*setAnimatedDurations)(void* object, const void* durationsVec);
    void (*loadSyncAnimated)(void* object, int32_t* width, int32_t* height, int32_t* errorCode);
    void* (*getAnimatedController)(void* object, const char* id);
    void (*startAnimated)(void* object);
    void (*stopAnimated)(void* object);
    void (*pauseAnimated)(void* object);
    void (*resumeAnimated)(void* object);
    int32_t (*getAnimatedStatus)(void* object);
};

__attribute__((visibility("default"))) const ArkUIDrawableDescriptor* GetArkUIDrawableDescriptor(void);

#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_DRAWABLE_DRAWABLE_API_H