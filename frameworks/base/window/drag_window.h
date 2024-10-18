/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_WINDOW_ACE_DRAG_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_WINDOW_ACE_DRAG_WINDOW_H

#include "base/geometry/offset.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"

#ifndef USE_GRAPHIC_TEXT_GINE
namespace txt {
class Paragraph;
}
#else
namespace OHOS::Rosen {
class Typography;
}
#endif

namespace OHOS::Ace {

class RenderText;

namespace NG {
class FrameNode;
class Paragraph;
class TextPattern;
} // namespace NG

class ACE_EXPORT DragWindow : public AceType {
    DECLARE_ACE_TYPE(DragWindow, AceType);

public:
    struct DragWindowParams {
        std::string windowName;
        int32_t x = 0;
        int32_t y = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        int32_t parentWindowId = -1;
    };

    static RefPtr<DragWindow> CreateDragWindow(
        const std::string& windowName, int32_t x, int32_t y, uint32_t width, uint32_t height);
    static RefPtr<DragWindow> CreateDragWindow(const DragWindowParams& params);

    static RefPtr<DragWindow> CreateTextDragWindow(
        const std::string& windowName, int32_t x, int32_t y, uint32_t width, uint32_t height);
    virtual void MoveTo(int32_t x, int32_t y) const = 0;
    virtual void TextDragWindowMove(double x, double y) const = 0;
    virtual void Destroy() const = 0;
    virtual void DrawPixelMap(const RefPtr<PixelMap>& pixelmap) = 0;
    virtual void DrawFrameNode(const RefPtr<NG::FrameNode>& rootNode) = 0;
    virtual void DrawImage(void* drawingImage) = 0;
#ifndef USE_GRAPHIC_TEXT_GINE
    virtual void DrawText(
        std::shared_ptr<txt::Paragraph> paragraph, const Offset& offset, const RefPtr<RenderText>& renderText) = 0;
#else
    virtual void DrawText(
        std::shared_ptr<Rosen::Typography> paragraph_, const Offset& offset, const RefPtr<RenderText>& renderText) = 0;
#endif
    virtual void DrawTextNG(const RefPtr<NG::Paragraph>& paragraph, const RefPtr<NG::TextPattern>& textPattern) = 0;

    void SetOffset(int32_t offsetX, int32_t offsetY)
    {
        offsetX_ = offsetX;
        offsetY_ = offsetY;
    }

    void SetSize(int32_t width, int32_t height)
    {
        width_ = width;
        height_ = height;
    }

protected:
    int32_t width_ = 0;
    int32_t height_ = 0;
    int32_t offsetX_ = 0;
    int32_t offsetY_ = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_WINDOW_ACE_DRAG_WINDOW_H
