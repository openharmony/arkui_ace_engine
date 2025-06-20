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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVDESTINATION_SCROLLABLE_PROCESSOR_H

#include "gmock/gmock.h"

#define protected public
#define private public
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"

namespace OHOS::Ace::NG {

class MockNavDestinationScrollableProcessor : public NavDestinationScrollableProcessor {
    DECLARE_ACE_TYPE(MockNavDestinationScrollableProcessor, NavDestinationScrollableProcessor);
public:
    MockNavDestinationScrollableProcessor() = default;
    ~MockNavDestinationScrollableProcessor() = default;

    MOCK_METHOD0(UpdateBindingRelation, void());
    MOCK_METHOD1(SetNodeId, void(int32_t));
    MOCK_METHOD1(SetNavDestinationPattern, void(WeakPtr<NavDestinationPattern>));
    MOCK_METHOD0(UnbindAllScrollers, void());
};
} // namespace NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
