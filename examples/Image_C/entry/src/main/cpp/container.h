/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef MYAPPLICATION_CONTAINER_H
#define MYAPPLICATION_CONTAINER_H

#include <string>
#include <unordered_map>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;

namespace NativeXComponentSample {

class Container {
public:
    explicit Container(const std::string &id);
    ~Container() = default;
    static Container *GetInstance(const std::string &id);
    static void Release(const std::string &id);
    void Export(napi_env env, napi_value exports);
    void OnSurfaceChanged(OH_NativeXComponent *component, void *window);
    void OnTouchEvent(OH_NativeXComponent *component, void *window);
    void OnMouseEvent(OH_NativeXComponent *component, void *window);
    void OnHoverEvent(OH_NativeXComponent *component, bool isHover);
    void OnKeyEvent(OH_NativeXComponent *component, void *window);
    void RegisterCallback(OH_NativeXComponent *nativeXComponent);

public:
    static std::unordered_map<std::string, Container *> instance_;
    std::string id_;

private:
    OH_NativeXComponent_Callback containerCallback_;
    OH_NativeXComponent_MouseEvent_Callback mouseCallback_;
};

} // namespace NativeXComponentSample


#endif //MYAPPLICATION_CONTAINER_H
