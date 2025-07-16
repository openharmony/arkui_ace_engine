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

#include "NativeRenderer.h"
#include "SkSurface.h"

class NativeSoftwareRenderer : public NativeRenderer {
public:
    NativeSoftwareRenderer(int width, int height, SkoalaNativeRenderer* renderer) : NativeRenderer(width, height, renderer) {
        if (makeSurface()) {
            if (renderer) {
                renderer->onInit(renderer, nullptr, width, height);
                uintptr_t pixelsPtr = reinterpret_cast<uintptr_t>(pixels->writable_data());
                renderer->sendMessage(renderer, SkoalaNativeRendererIdPixels,
                    (pixelsPtr & 0xffffffff), (pixelsPtr >> 32), colorType, 0, 0, 0);
            }
        }
    }
    ~NativeSoftwareRenderer() override {}

    void draw() override {
        renderer->onDraw(renderer, width, height);
    }

private:
    sk_sp<SkData> pixels;
    SkColorType colorType;
    bool makeSurface() {
        pixels = SkData::MakeUninitialized(width * height * 4);
        auto imageInfo = SkImageInfo::Make(width, height, kBGRA_8888_SkColorType, kUnpremul_SkAlphaType);
        colorType = imageInfo.colorType();
        drawSurface = SkSurfaces::WrapPixels(imageInfo, pixels->writable_data(), width * 4);
        return true;
    }
};

void impl_skoala_TexturedImage__1nDraw(KNativePointer ptr) {
    NativeRenderer* renderer = reinterpret_cast<NativeRenderer*>(ptr);
    renderer->draw();
}
KOALA_INTEROP_V1(skoala_TexturedImage__1nDraw, KNativePointer)

KNativePointer impl_skoala_TexturedImage__1nGetSurface(KNativePointer ptr) {
    NativeRenderer* renderer = reinterpret_cast<NativeRenderer*>(ptr);
    return renderer->releaseSurface();
}
KOALA_INTEROP_1(skoala_TexturedImage__1nGetSurface, KNativePointer, KNativePointer)

KNativePointer impl_skoala_TexturedImage__1nMakeNativeSoftwareRenderer(KInt width, KInt height, KNativePointer nativeRendererPtr) {
    SkoalaNativeRenderer* nativeRenderer = reinterpret_cast<SkoalaNativeRenderer*>(nativeRendererPtr);
    NativeSoftwareRenderer* renderer = new NativeSoftwareRenderer(width, height, nativeRenderer);
    return renderer;
}
KOALA_INTEROP_3(skoala_TexturedImage__1nMakeNativeSoftwareRenderer, KNativePointer, KInt, KInt, KNativePointer)

static void deleteNativeRenderer(NativeRenderer* ptr) {
    if (ptr) delete ptr;
}
KNativePointer impl_skoala_TexturedImage__1nGetFinalizer() {
    return fnPtr<NativeRenderer>(&deleteNativeRenderer);
}
KOALA_INTEROP_0(skoala_TexturedImage__1nGetFinalizer, KNativePointer)
