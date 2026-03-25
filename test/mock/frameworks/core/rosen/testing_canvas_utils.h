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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_UTILS_H

#include "testing_canvas.h"

struct NativeWindow;
typedef struct NativeWindow OHNativeWindow;
namespace OHOS::Ace::Testing {
class TestingCanvasUtils {
public:
    static TestingCanvasUtils* GetInstance()
    {
        static TestingCanvasUtils canvasUtils;
        return &canvasUtils;
    }
    static TestingCanvas* CreateLockCanvas(OHNativeWindow* nativeWindow)
    {
        auto canvasUtils = GetInstance();
        if (canvasUtils->lockCanvas == nullptr) {
            canvasUtils->lockCanvas = new TestingCanvas();
            return canvasUtils->lockCanvas;
        }
        return nullptr;
    }
    static bool UnlockCanvas(TestingCanvas* canvas, OHNativeWindow* nativeWindow)
    {
        auto canvasUtils = GetInstance();
        if (canvasUtils->lockCanvas == nullptr) {
            return false;
        }
        delete canvasUtils->lockCanvas;
        canvasUtils->lockCanvas = nullptr;
        return true;
    }
    ~TestingCanvasUtils()
    {
        if (lockCanvas != nullptr) {
            delete lockCanvas;
            lockCanvas = nullptr;
        }
    }
    TestingCanvas* lockCanvas = nullptr;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_UTILS_H
