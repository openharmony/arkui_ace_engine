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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_SURFACE_H

#include "gmock/gmock.h"

#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
class MockRenderSurface : public RenderSurface {
    DECLARE_ACE_TYPE(MockRenderSurface, RenderSurface);
public:
    ~MockRenderSurface() override = default;
    MOCK_CONST_METHOD0(IsSurfaceValid, bool());
    MOCK_METHOD2(AdjustNativeWindowSize, void(uint32_t, uint32_t));
    MOCK_METHOD2(ConfigSurface, void(uint32_t, uint32_t));
    MOCK_METHOD4(SetExtSurfaceBounds, void(int32_t, int32_t, int32_t, int32_t));
    MOCK_METHOD0(ReleaseSurfaceBuffers, void());
    MOCK_METHOD1(SetInstanceId, void(int32_t));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_SURFACE_H
