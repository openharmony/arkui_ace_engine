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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_SIDE_BAR_CONTAINER_SIDE_BAR_CONTAINER_TEST_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_SIDE_BAR_CONTAINER_SIDE_BAR_CONTAINER_TEST_UTILS_H

#include "core/components/box/render_box.h"
#include "core/components/display/render_display.h"
#include "core/components/side_bar/render_side_bar_container.h"

namespace OHOS::Ace {
class MockRenderBox final : public RenderBox {
    DECLARE_ACE_TYPE(MockRenderBox, RenderBox);

public:
    MockRenderBox() = default;
    ~MockRenderBox() override = default;
};

class MockRenderSideBarContainer final : public RenderSideBarContainer {
    DECLARE_ACE_TYPE(MockRenderSideBarContainer, RenderSideBarContainer);

public:
    MockRenderSideBarContainer() = default;
    ~MockRenderSideBarContainer() = default;
};

class MockRenderDisplay final : public RenderDisplay {
    DECLARE_ACE_TYPE(MockRenderDisplay, RenderDisplay);

public:
    MockRenderDisplay() = default;
    ~MockRenderDisplay() = default;
};

class SideBarContainerTestUtils {
public:
    static RefPtr<RenderBox> CreateRenderBox(double width, double height);
    static RefPtr<RenderDisplay> CreateRenderDisplay();
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_SIDE_BAR_CONTAINER_SIDE_BAR_CONTAINER_TEST_UTILS_H