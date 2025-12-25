/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/form/form_pattern.h"

#include "mock_form_manager_delegate.h"
#include "core/components/form/sub_container.h"

#include "pointer_event.h"

namespace OHOS::Ace::NG {
FormPattern::FormPattern() = default;
FormPattern::~FormPattern() = default;

const RefPtr<SubContainer>& FormPattern::GetSubContainer() const
{
    return subContainer_;
}

void FormPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture)
{
}

bool FormPattern::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
}

void FormPattern::OnAccessibilityChildTreeDeregister()
{
}

void FormPattern::OnAccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
}

void FormPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto info = layoutProperty->GetRequestFormInfo().value_or(RequestFormInfo());
    layoutProperty->UpdateRequestFormInfo(info);
}

bool FormPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return false;
}

void FormPattern::OnRebuildFrame()
{
}

void FormPattern::OnVisibleChange(bool isVisible)
{
}

void FormPattern::OnLanguageConfigurationUpdate()
{
}

RefPtr<AccessibilitySessionAdapter> FormPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void FormPattern::OnAttachToFrameNode()
{
}

void FormPattern::DumpInfo()
{
}

void FormPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
}

bool FormPattern::OnAccessibilityStateChange(bool state)
{
    return false;
}

void FormPattern::OnColorConfigurationUpdate()
{
}
} // namespace OHOS::Ace::NG