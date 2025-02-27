/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_ADAPTER_OHOS_CAPABILITY_CONVERT_TEST_TOOLS_H
#define FOUNDATION_ACE_TEST_UNITTEST_ADAPTER_OHOS_CAPABILITY_CONVERT_TEST_TOOLS_H

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "html_to_span.h"
#include "span_to_html.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/measure_property.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {

class HtmlConvertTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    bool IsSpanItemSame(std::list<RefPtr<NG::SpanItem>> src, std::list<RefPtr<NG::SpanItem>> other);
    SpanParagraphStyle GetDefaultParagraphStyle();

    ImageSpanOptions GetImageOption(const std::string& src);
    static ImageSpanOptions GetImageOption(
        const std::string& src,
        const Dimension& width,
        const Dimension& height,
        ImageFit fit = ImageFit::CONTAIN,
        VerticalAlign align = VerticalAlign::CENTER,
        const BorderRadiusProperty& borderRadius = BorderRadiusProperty(),
        const MarginProperty& margins = MarginProperty(),
        const PaddingProperty& paddings = PaddingProperty()
    );
};
};
#endif // FOUNDATION_ACE_TEST_UNITTEST_ADAPTER_OHOS_CAPABILITY_CONVERT_TEST_TOOLS_H