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

#include <benchmark/benchmark.h>
#include <iostream>

#include "arkoala_api_generated.h"
#include "benchmark_assert.h"
#include "core/pipeline/base/element_register.h"
using namespace std;

namespace OHOS::Ace::NG {
extern "C" const OH_AnyAPI* GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind kind, int version);

class BenchmarkButtonTest : public benchmark::Fixture {
public:
    BenchmarkButtonTest()
    {
        Iterations(iterations);
        Repetitions(repetitions);
        ReportAggregatesOnly(true);
    }

    ~BenchmarkButtonTest() override = default;
    Ark_NodeHandle node_ = nullptr;

    auto GetId()
    {
        return ElementRegister::GetInstance()->MakeUniqueId();
    }

    Ark_NodeHandle CreateNode()
    {
        return static_cast<Ark_NodeHandle>(CreateNodeImpl());
    }

    virtual void *CreateNodeImpl()
    {
        if (modifier_) {
            return modifier_->construct(GetId(), 0);;
        } else {
            cout << "Modifier pointer is nullptr. Node is not created!" << std::endl;
            return nullptr;
        }
    }

    virtual void DisposeNode(Ark_NodeHandle &node)
    {
        if (basicAPI_) {
            basicAPI_->disposeNode(node);
        }
        node = nullptr;
    }

    void SetUp(const ::benchmark::State& state) override
    {
    };

    void TearDown(const ::benchmark::State& state) override
    {
    }

protected:
    const int32_t repetitions = 3;
    const int32_t iterations = 1000;

    inline static const GENERATED_ArkUIBasicNodeAPI *basicAPI_
        = reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_BASIC,
            GENERATED_ARKUI_BASIC_NODE_API_VERSION)
        );
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL,
            GENERATED_ARKUI_FULL_API_VERSION)
        );
    const GENERATED_ArkUINodeModifiers *nodeModifiers_
        = fullAPI_ ? fullAPI_->getNodeModifiers() : nullptr;

    const GENERATED_ArkUIButtonModifier *modifier_
        = nodeModifiers_ && nodeModifiers_->getButtonModifier ? nodeModifiers_->getButtonModifier() : nullptr;
};

/**
 * @tc.name: test_button_create_default
 * @tc.desc: create and map ashmem
 * @tc.type: FUNC
 */
BENCHMARK_F(BenchmarkButtonTest, test_button_create_default)(benchmark::State& state)
{
    cout << "ButtonTest test_button_create_default RUN." << std::endl;
    while (state.KeepRunning()) {

        //SetUp sources:
        AssertUnequal(modifier_, nullptr, "ButtonModifier is nullptr.", state);
        node_ = CreateNode();
        AssertUnequal(node_, nullptr, "ButtonNode is nullptr.", state);

        //TearDown sources:
        DisposeNode(node_);
    }
    cout << "ButtonTest test_button_create_default FINISH." << std::endl;
}

}  // namespace OHOS::Ace::NG
// Run the benchmark
BENCHMARK_MAIN();