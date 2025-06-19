/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "frameworks/core/components/image/image_component.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageCommonMethods {
// similar as in the js_image.cpp/js_image_span.cpp
const std::vector<float> DEFAULT_COLORFILTER_MATRIX = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0
};

void ApplyColorFilterValues(Ark_NativePointer node, const Opt_Union_ColorFilter_DrawingColorFilter* value);
} // namespace ImageCommonMethods
} // namespace OHOS::Ace::NG::GeneratedModifier
