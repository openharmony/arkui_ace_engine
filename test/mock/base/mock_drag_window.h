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

    MOCK_METHOD1(DrawImage, void(void* skImage));
#ifndef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD3(DrawText,
        void(std::shared_ptr<txt::Paragraph> paragraph, const Offset& offset, const RefPtr<RenderText>& renderText));
#else
    MOCK_METHOD3(DrawText,
        void(std::shared_ptr<Rosen::Typography> paragraph, const Offset& offset, const RefPtr<RenderText>& renderText));
#endif
    MOCK_METHOD2(DrawTextNG, void(const RefPtr<NG::Paragraph>& paragraph, const RefPtr<NG::TextPattern>& textPattern));
    MOCK_METHOD1(DrawPixelMap, void(const RefPtr<PixelMap>&));
    MOCK_METHOD1(DrawFrameNode, void(const RefPtr<NG::FrameNode>&));
    MOCK_CONST_METHOD2(MoveTo, void(int32_t, int32_t));
    MOCK_CONST_METHOD0(Destroy, void());
    MOCK_CONST_METHOD2(TextDragWindowMove, void(double x, double y));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_DRAG_WINDOW_H
