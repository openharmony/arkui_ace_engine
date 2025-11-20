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

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/drawing_canvas_peer_impl.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "arkoala_api_generated.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace {
constexpr int SIZE = 200;
constexpr int START = 0;
constexpr int END = 100;

class MockPattern : public NG::OffscreenCanvasPattern {
public:
    MockPattern() : NG::OffscreenCanvasPattern(SIZE, SIZE) {}
    ~MockPattern() override = default;
    MOCK_METHOD(void, FillRect, (const Rect&));
};
} // namespace

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestMyBase : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }
};

} // namespace OHOS::Ace::NG
