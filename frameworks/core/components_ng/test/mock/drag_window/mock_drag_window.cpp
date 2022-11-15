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
#include "core/components_ng/test/mock/drag_window/mock_drag_window.h"

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
RefPtr<DragWindow> DragWindow::CreateDragWindow(
    const std::string& windowName, int32_t x, int32_t y, uint32_t width, uint32_t height)
{
    return AceType::MakeRefPtr<MockDragWindow>();
}

void MockDragWindow::MoveTo(int32_t x, int32_t y) const
{
    GTEST_LOG_(INFO) << "DragWindow move to "
                     << "(" << x << ", " << y << ").";
}

void MockDragWindow::DrawPixelMap(const RefPtr<PixelMap>& pixelmap)
{
    GTEST_LOG_(INFO) << "DrawPixelMap has called";
}

void MockDragWindow::DrawFrameNode(const RefPtr<NG::FrameNode>& rootNode)
{
    GTEST_LOG_(INFO) << "DrawFrameNode has called";
}

void MockDragWindow::Destroy() const
{
    GTEST_LOG_(INFO) << "Destroy has called";
}
} // namespace OHOS::Ace
