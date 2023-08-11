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

#include "test/mock/core/common/mock_container.h"

#include "core/common/container.h"

namespace OHOS::Ace {
namespace {
int32_t g_id = 0;
} // namespace

RefPtr<MockContainer> MockContainer::container_;
bool Frontend::MaybeRelease()
{
    return AceType::MaybeRelease();
}

int32_t Container::CurrentId()
{
    return g_id;
}

RefPtr<Container> Container::GetActive()
{
    RefPtr<Container> activeContainer;
    return activeContainer;
}

RefPtr<TaskExecutor> Container::CurrentTaskExecutor()
{
    return MockContainer::Current()->GetTaskExecutor();
}

void Container::UpdateCurrent(int32_t id)
{
    g_id = id;
}

RefPtr<Container> Container::Current()
{
    return MockContainer::Current();
}

bool Container::Dump(const std::vector<std::string>& /* params */, std::vector<std::string>& /* info */)
{
    return true;
}

void MockContainer::SetUp()
{
    container_ = AceType::MakeRefPtr<MockContainer>();
}

void MockContainer::TearDown()
{
    container_ = nullptr;
}

RefPtr<MockContainer> MockContainer::Current()
{
    return container_;
}
} // namespace OHOS::Ace
