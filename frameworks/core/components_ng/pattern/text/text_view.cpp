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

#include "core/components_ng/pattern/text/text_view.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_modifier.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void TextView::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // TODO: Add unique id.
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    stack->Push(frameNode);
    stack->PushLayoutTask(ContentModifier(content));
}

void TextView::FontSize(const Dimension& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(FontSizeModifier(value));
}

void TextView::TextColor(const Color& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(FontColorModifier(value));
}

void TextView::ItalicFontStyle(const NG::ItalicFontStyle& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(ItalicFontStyleModifier(value));
}

void TextView::FontWeight(const Ace::FontWeight& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(FontWeightModifier(value));
}

void TextView::FontFamily(const std::vector<std::string>& value)
{
    ViewStackProcessor::GetInstance()->PushLayoutTask(FontFamilyModifier(value));
}
} // namespace OHOS::Ace::NG
