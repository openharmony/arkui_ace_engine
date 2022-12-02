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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_DRAG_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_DRAG_WINDOW_H

#include "gmock/gmock.h"

#include "base/window/drag_window.h"

namespace OHOS::Ace {
class MockDragWindow : public DragWindow {
    DECLARE_ACE_TYPE(MockDragWindow, DragWindow);

public:
    MockDragWindow() = default;
    ~MockDragWindow() override = default;

    void MoveTo(int32_t x, int32_t y) const override;
    void DrawPixelMap(const RefPtr<PixelMap>& pixelMap) override;
    void DrawFrameNode(const RefPtr<NG::FrameNode>& rootNode) override;
    void Destroy() const override;

    MOCK_METHOD1(DrawImage, void(void* skImage));
    MOCK_METHOD3(DrawText,
        void(std::shared_ptr<txt::Paragraph> paragraph_, const Offset& offset, const RefPtr<RenderText>& renderText));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_DRAG_WINDOW_H
