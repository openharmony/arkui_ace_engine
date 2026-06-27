/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "ui/view/components/symbol.h"
#include "ui/base/ace_type.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;
using namespace OHOS::Ace::Kit;

namespace {
const int32_t TEST_NODE_ID = 10001;
}

namespace OHOS::Ace::Kit {

class SymbolTest : public testing::Test {
protected:
    void SetUp() override
    {
        NG::MockPipelineContext::SetUp();
        auto aceNode = NG::SymbolModelNG::CreateFrameNode(TEST_NODE_ID);
        ASSERT_NE(aceNode, nullptr);
        auto frameNodeImpl = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
        RefPtr<Kit::FrameNode> baseNode = frameNodeImpl;
        symbol_ = AceType::MakeRefPtr<Symbol>(baseNode);
    }

    void TearDown() override
    {
        symbol_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }

    RefPtr<NG::FrameNode> GetAceSymbolNode()
    {
        auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(symbol_->node_);
        if (!frameNodeImpl) {
            return nullptr;
        }
        auto aceNode = frameNodeImpl->GetAceNode();
        if (!aceNode) {
            return nullptr;
        }
        return AceType::DynamicCast<NG::FrameNode>(aceNode);
    }

    NG::TextPattern* GetTextPattern()
    {
        auto symbolNode = GetAceSymbolNode();
        if (!symbolNode) {
            return nullptr;
        }
        auto pattern = symbolNode->GetPattern<NG::TextPattern>();
        return pattern ? pattern.GetRawPtr() : nullptr;
    }

    NG::TextLayoutProperty* GetTextLayoutProperty()
    {
        auto symbolNode = GetAceSymbolNode();
        if (!symbolNode) {
            return nullptr;
        }
        auto property = symbolNode->GetLayoutProperty<NG::TextLayoutProperty>();
        return property ? property.GetRawPtr() : nullptr;
    }
 
protected:
    RefPtr<Symbol> symbol_;
};

HWTEST_F(SymbolTest, SymbolTest_SetFontColorResourceFlag, TestSize.Level1)
{
    symbol_->SetIsFontColorResource(true);
    auto property = GetTextLayoutProperty();
    ASSERT_NE(property, nullptr);
    auto result = property->GetIsFontColorResource().value_or(false);
    EXPECT_EQ(result, true);
}

HWTEST_F(SymbolTest, SymbolTest_SetFontColorResource, TestSize.Level1)
{
    auto property = GetTextLayoutProperty();
    ASSERT_NE(property, nullptr);
    property->UpdateFontColorResource({});
    auto result = symbol_->GetSymbolFontObjColor();
    EXPECT_EQ(result.size(), 0);
}

HWTEST_F(SymbolTest, SymbolTest, TestSize.Level1)
{
    auto property = GetTextLayoutProperty();
    ASSERT_NE(property, nullptr);
    property->UpdateSymbolColorList({});
    auto result = symbol_->GetSymbolFontColor();
    EXPECT_EQ(result.size(), 0);
}
} // namespace OHOS::Ace::Kit
