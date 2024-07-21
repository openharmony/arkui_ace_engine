/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/stage/content_root_pattern.h"

#include "core/components/container_modal/container_modal_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ContentRootPattern::BeforeCreateLayoutWrapper()
{
    auto inset = CreateSafeAreaInsets();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto props = host->GetLayoutProperty();
    if (inset.IsValid() || props->GetSafeAreaInsets()) {
        props->UpdateSafeAreaInsets(inset);
    }
}

SafeAreaInsets ContentRootPattern::CreateSafeAreaInsets() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, {});

    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(manager, {});
    auto inset = manager->GetSafeAreaWithoutCutout();

    // popups does not avoid cutout area here
    if (AvoidCutout()) {
        inset = inset.Combine(manager->GetCutoutSafeArea());
    }

    if (!AvoidBottom()) {
        inset.bottom_ = { 0, 0 };
    }

    if (AvoidKeyboard()) {
        inset.bottom_ = inset.bottom_.Combine(manager->GetKeyboardInset());
    }

    // not full-screen in floating window mode, calculate real inset
    if (inset.bottom_.IsValid() && pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
        pipeline->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        auto titleHeight = pipeline->GetCustomTitleHeight().ConvertToPx();
        auto borderWidth = CONTAINER_BORDER_WIDTH.ConvertToPx();
        auto botPadding = CONTENT_PADDING.ConvertToPx();
        inset.bottom_.start -= std::round(titleHeight + borderWidth);
        inset.bottom_.end -= std::round(titleHeight + 2 * borderWidth + botPadding);
    }

    if (!AvoidTop()) {
        inset.top_ = { 0, 0 };
    }
    LOGD("create root content safeAreaInsets: AvoidKeyboard %{public}d, AvoidTop %{public}d, AvoidCutout %{public}d, "
         "inset %{public}s",
        AvoidKeyboard(), AvoidTop(), AvoidCutout(), inset.ToString().c_str());
    return inset;
}
} // namespace OHOS::Ace::NG