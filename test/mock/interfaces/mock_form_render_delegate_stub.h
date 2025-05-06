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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_MOCK_FORM_RENDER_DELEGATE_STUB_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_MOCK_FORM_RENDER_DELEGATE_STUB_H

#include "gmock/gmock.h"

#include "iremote_broker.h"
#include "iremote_object.h"

namespace OHOS {
namespace Ace {
class MockFormRenderDelegateStub : public FormRendererDelegateStub {
public:
    MOCK_METHOD3(OnSurfaceCreate, int32_t(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want));
    MOCK_METHOD3(OnSurfaceReuse, int32_t(uint64_t surfaceId, const AppExecFwk::FormJsInfo& formJsInfo,
        const AAFwk::Want& want));
    MOCK_METHOD1(OnSurfaceRelease, int32_t(uint64_t surfaceId));
    MOCK_METHOD1(OnActionEvent, int32_t(const std::string& action));
    MOCK_METHOD2(OnError, int32_t(const std::string& code, const std::string& msg));
    MOCK_METHOD3(OnSurfaceChange, int32_t(float width, float height, float borderWidth));
    MOCK_METHOD1(OnSurfaceDetach, int32_t(uint64_t surfaceId));
    MOCK_METHOD1(OnFormLinkInfoUpdate, int32_t(const std::vector<std::string>& formLinkInfos));
    MOCK_METHOD1(OnGetRectRelativeToWindow, int32_t(AccessibilityParentRectInfo& parentRectInfo));
    MOCK_METHOD1(OnCheckManagerDelegate, int32_t(bool &checkFlag));
    MOCK_METHOD1(OnUpdateFormDone, int32_t(const int64_t formId));
};
} // namespace Ace
} // namespace OHOS
#endif
