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

#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "ecmascript/napi/include/jsnapi.h"
#include <unordered_map>

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUISearchModifier* GetSearchStaticModifier();
const GENERATED_ArkUICounterModifier* GetCounterStaticModifier();
const GENERATED_ArkUIPatternLockModifier* GetPatternLockStaticModifier();
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphStaticModifier();
const GENERATED_ArkUITextClockModifier* GetTextClockStaticModifier();
}

namespace OHOS::Ace {

namespace {
class TestDynamicModule : public DynamicModule {
public:
    explicit TestDynamicModule(const std::string& name) : name_(name) {}

    void RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) override {}

    const void* GetDynamicModifier() override { return nullptr; }
    const void* GetStaticModifier() override
    {
        if (name_ == "Search") {
            return reinterpret_cast<const void*>(OHOS::Ace::NG::GeneratedModifier::GetSearchStaticModifier());
        }
        if (name_ == "Counter") {
            return reinterpret_cast<const void*>(OHOS::Ace::NG::GeneratedModifier::GetCounterStaticModifier());
        }
        if (name_ == "PatternLock") {
            return reinterpret_cast<const void*>(OHOS::Ace::NG::GeneratedModifier::GetPatternLockStaticModifier());
        }
        if (name_ == "SymbolGlyph") {
            return reinterpret_cast<const void*>(OHOS::Ace::NG::GeneratedModifier::GetSymbolGlyphStaticModifier());
        }
        if (name_ == "TextClock") {
            return reinterpret_cast<const void*>(OHOS::Ace::NG::GeneratedModifier::GetTextClockStaticModifier());
        }
        return nullptr;
    }
    const void* GetCjModifier() override { return nullptr; }

private:
    std::string name_;
};

std::unordered_map<std::string, std::unique_ptr<TestDynamicModule>>& GetModuleMap()
{
    static std::unordered_map<std::string, std::unique_ptr<TestDynamicModule>> map;
    return map;
}
} // namespace

DynamicModule* DynamicModuleHelper::GetDynamicModule(const std::string& name)
{
    auto& map = GetModuleMap();
    auto it = map.find(name);
    if (it != map.end()) {
        return it->second.get();
    }
    auto module = std::make_unique<TestDynamicModule>(name);
    auto* raw = module.get();
    map[name] = std::move(module);
    return raw;
}
} // namespace OHOS::Ace
