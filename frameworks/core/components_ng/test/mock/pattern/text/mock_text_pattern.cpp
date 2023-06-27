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

#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
TextPattern::~TextPattern() = default;

void TextPattern::OnDetachFromFrameNode(FrameNode* node) {}

void TextPattern::HandleLongPress(GestureEvent& info) {}

void TextPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle) {}

void TextPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle) {}

void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle) {}

void TextPattern::HandleOnSelectAll() {}

void TextPattern::OnModifyDone() {}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return true;
}

void TextPattern::BeforeCreateLayoutWrapper() {}

void TextPattern::OnVisibleChange(bool isVisible) {}

void TextPattern::DumpInfo() {}

float TextPattern::GetLineHeight() const
{
    return {};
}

std::vector<RSTypographyProperties::TextBox> TextPattern::GetTextBoxes()
{
    return {};
}
OffsetF TextPattern::GetParentGlobalOffset() const
{
    return {};
}

void TextPattern::CloseSelectOverlay()
{
}
void TextPattern::CreateHandles()
{
}

bool TextPattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    return {};
}

void TextPattern::InitSurfaceChangedCallback() {}
void TextPattern::OnAttachToFrameNode() {}
} // namespace OHOS::Ace::NG
