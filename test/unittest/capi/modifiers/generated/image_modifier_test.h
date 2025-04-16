/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_IMAGE_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_IMAGE_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace TestConst::Image {
const auto ATTRIBUTE_IMAGE_AIOPTIONS_NAME = "imageAIOptions";
const auto ATTRIBUTE_SOURCE_SIZE_NAME = "sourceSize";
const auto ATTRIBUTE_ANALYZER_CONFIG_NAME = "analyzerConfig";
const auto ATTRIBUTE_RESIZABLE_NAME = "resizable";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_NAME = "slice";
const auto ATTRIBUTE_SRC_NAME = "src";
const auto ATTRIBUTE_SRC_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_NAME = "types";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_NAME = "aiController";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALT_NAME = "alt";
const auto ATTRIBUTE_ALT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME = "matchTextDirection";
const auto ATTRIBUTE_MATCH_TEXT_DIRECTION_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME = "fitOriginalSize";
const auto ATTRIBUTE_FIT_ORIGINAL_SIZE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_OBJECT_FIT_NAME = "objectFit";
const auto ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE = "ImageFit.Cover";
const auto ATTRIBUTE_OBJECT_REPEAT_NAME = "objectRepeat";
const auto ATTRIBUTE_OBJECT_REPEAT_DEFAULT_VALUE = "ImageRepeat.NoRepeat";
const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_RENDER_MODE_NAME = "renderMode";
const auto ATTRIBUTE_RENDER_MODE_DEFAULT_VALUE = "ImageRenderMode.Original";
const auto ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME = "dynamicRangeMode";
const auto ATTRIBUTE_DYNAMIC_RANGE_MODE_DEFAULT_VALUE = "dynamicRangeMode.Standard";
const auto ATTRIBUTE_INTERPOLATION_NAME = "interpolation";
const auto ATTRIBUTE_INTERPOLATION_DEFAULT_VALUE = "ImageInterpolation.None";
const auto ATTRIBUTE_SOURCE_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_SOURCE_SIZE_I_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SYNC_LOAD_NAME = "syncLoad";
const auto ATTRIBUTE_SYNC_LOAD_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_COLOR_FILTER_NAME = "colorFilter";
const auto ATTRIBUTE_COLOR_FILTER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "CopyOptions.None";
const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_EDGE_ANTIALIASING_NAME = "edgeAntialiasing";
const auto ATTRIBUTE_EDGE_ANTIALIASING_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ENABLE_ANALYZER_NAME = "enableAnalyzer";
const auto ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_NAME = "types";
const auto ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_NAME = "top";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_NAME = "left";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ORIENTATION_NAME = "orientation";
const auto ATTRIBUTE_ORIENTATION_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace TestConst::Image

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier,
                              &GENERATED_ArkUINodeModifiers::getImageModifier, GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_IMAGE_H
