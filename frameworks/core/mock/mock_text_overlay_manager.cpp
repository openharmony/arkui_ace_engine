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

#include "core/components/text_overlay/text_overlay_manager.h"
#include "core/components/text_overlay/text_overlay_component.h"

namespace OHOS::Ace {
TextOverlayBase::~TextOverlayBase() = default;

Offset TextOverlayBase::MakeEmptyOffset() const
{
    return Offset();
}

double TextOverlayBase::GetBoundaryOfParagraph(bool isLeftBoundary) const
{
    return 0.0;
}

bool TextOverlayBase::ComputeOffsetForCaretUpstream(int32_t extent, CaretMetrics& result) const
{
    return true;
}

bool TextOverlayBase::ComputeOffsetForCaretDownstream(int32_t extent, CaretMetrics& result) const
{
    return true;
}

bool TextOverlayBase::ComputeOffsetForCaretCloserToClick(int32_t extent, CaretMetrics& result) const
{
    return true;
}

DirectionStatus TextOverlayBase::GetDirectionStatusOfPosition(int32_t position) const
{
    return static_cast<DirectionStatus>(0);
}

bool TextOverlayBase::GetCaretRect(int32_t extent, Rect& caretRect, double caretHeightOffset) const
{
    return true;
}

int32_t TextOverlayBase::GetCursorPositionForClick(const Offset& offset, const Offset& globalOffset)
{
    return 0;
}

int32_t TextOverlayBase::GetGraphemeClusterLength(int32_t extend, bool isPrefix) const
{
    return 0;
}

void TextOverlayBase::InitAnimation(const WeakPtr<PipelineContext>& pipelineContext)
{
}

void TextOverlayBase::PaintSelection(SkCanvas* canvas, const Offset& globalOffset)
{
}

void TextOverlayBase::InitSelection(const Offset& pos, const Offset& globalOffset)
{
}

void TextOverlayBase::UpdateStartSelection(int32_t end, const Offset& pos, const Offset& globalOffset)
{
}

void TextOverlayBase::UpdateEndSelection(int32_t start, const Offset& pos, const Offset& globalOffset)
{
}

void TextOverlayBase::ChangeSelection(int32_t start, int32_t end)
{
}

RefPtr<TextOverlayManager> TextOverlayBase::GetTextOverlayManager(const WeakPtr<PipelineContext>& pipelineContext)
{
    return nullptr;
}

TextOverlayManager::TextOverlayManager(const WeakPtr<PipelineContext>& context)
{
    context_ = context;
}

TextOverlayManager::~TextOverlayManager() = default;

const RefPtr<RenderNode> TextOverlayManager::GetTargetNode() const
{
    return nullptr;
}

void TextOverlayManager::PopTextOverlay()
{
}

void TextOverlayManager::PushTextOverlayToStack(const RefPtr<TextOverlayComponent>& textOverlay,
    const WeakPtr<PipelineContext>& pipelineContext)
{
}

void TextOverlayManager::HandleCtrlC() const
{
}

bool TextOverlayBase::IsSelectedText(const Offset& pos, const Offset& globalOffset)
{
    return true;
}
} // namespace OHOS::Ace
