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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H

#include <stdint.h>

#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"

namespace OHOS::Ace::Framework {

class JSRouteInfo : public NG::RouteInfo {
    DECLARE_ACE_TYPE(JSRouteInfo, NG::RouteInfo)
public:
    JSRouteInfo() = default;
    ~JSRouteInfo() override = default;

    std::string GetName() override;
    void SetName(const std::string& name);
    void SetParam(const JSRef<JSVal>& param);
    JSRef<JSVal> GetParam() const;

protected:
    std::string name_;
    JSRef<JSVal> param_;
};

class JSNavigationStack : public NG::NavigationStack {
    DECLARE_ACE_TYPE(JSNavigationStack, NG::NavigationStack)
public:
    JSNavigationStack() = default;
    ~JSNavigationStack() override = default;

    void UpdateStackInfo(const RefPtr<NavigationStack>& newStack) override
    {
        auto newJsStack = AceType::DynamicCast<JSNavigationStack>(newStack);
        if (newJsStack) {
            SetDataSourceObj(newJsStack->GetDataSourceObj());
        }
    }
    void SetDataSourceObj(const JSRef<JSObject>& dataSourceObj);
    const JSRef<JSObject>& GetDataSourceObj();
    void SetNavDestBuilderFunc(const JSRef<JSFunc>& navDestBuilderFunc);
    bool IsEmpty() override;
    void Pop() override;
    void Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo = nullptr) override;
    void Push(const std::string& name, int32_t index) override;
    void PushName(const std::string& name, const JSRef<JSVal>& param);
    void RemoveName(const std::string& name) override;
    void RemoveIndex(int32_t index) override;
    void Clear() override;
    std::vector<std::string> GetAllPathName() override;
    RefPtr<NG::UINode> CreateNodeByIndex(int32_t index) override;
    RefPtr<NG::UINode> CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo) override;
    void SetJSExecutionContext(const JSExecutionContext& context);

protected:
    JSRef<JSObject> dataSourceObj_;
    JSRef<JSFunc> navDestBuilderFunc_;
    JSExecutionContext executionContext_;

private:
    std::string GetNameByIndex(int32_t index);
    JSRef<JSVal> GetParamByIndex(int32_t index) const;
    bool CheckNavDestinationNodeInUINode(RefPtr<NG::UINode> node);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_STACK_H
