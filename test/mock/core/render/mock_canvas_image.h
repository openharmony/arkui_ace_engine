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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_MOCK_CANVAS_IMAGE__H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_MOCK_CANVAS_IMAGE__H

#include "gmock/gmock.h"

#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {
class MockCanvasImage : public CanvasImage {
    DECLARE_ACE_TYPE(MockCanvasImage, CanvasImage)
public:
    MockCanvasImage() = default;
    ~MockCanvasImage() override = default;
    MOCK_METHOD4(DrawToRSCanvas, void(RSCanvas&, const RSRect&, const RSRect&, const BorderRadiusArray&));
    MOCK_METHOD3(DrawRect, void(RSCanvas&, const RSRect&, const RSRect&));
    MOCK_CONST_METHOD0(GetWidth, int32_t());
    MOCK_CONST_METHOD0(GetHeight, int32_t());

    void SetRedrawCallback(std::function<void()>&& callback)  override
    {
        redrawCallback_ = callback;
    }

    void SetOnFinishCallback(std::function<void ()> &&callback) override
    {
        onFinishCallback_ = callback;
    }

    std::function<void()> redrawCallback_ = nullptr;
    std::function<void()> onFinishCallback_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_MOCK_CANVAS_IMAGE__H
