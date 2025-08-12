/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "common-interop.h"
#include "skoala.h"

#include "SkSurface.h"
#include "SkData.h"

enum {
    SkoalaNativeRendererIdFBO = 0,
    SkoalaNativeRendererIdMove = 1,
    SkoalaNativeRendererIdPointerPressed = 2,
    SkoalaNativeRendererIdPointerReleased = 3,
    SkoalaNativeRendererIdScroll = 4,
    SkoalaNativeRendererIdTick = 5,
    SkoalaNativeRendererIdRotate = 6,
    SkoalaNativeRendererIdPause = -1,
    SkoalaNativeRendererIdPixels = -2,    
};

class NativeRenderer {
protected:
    sk_sp<SkSurface> drawSurface;
    int width = 0;
    int height = 0;
    SkoalaNativeRenderer* renderer = nullptr;

public:
    NativeRenderer(int width, int height, SkoalaNativeRenderer* renderer) 
        : width(width), height(height), renderer(renderer) {}

    virtual ~NativeRenderer() {}

    SkSurface* releaseSurface() {
        return drawSurface.release();
    }

    virtual void draw() = 0;
};

