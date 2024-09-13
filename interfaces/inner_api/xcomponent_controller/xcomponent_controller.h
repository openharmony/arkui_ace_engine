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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_XCOMPONENT_CONTROLLER_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_XCOMPONENT_CONTROLLER_INTERFACE_H

#include <memory>

typedef struct napi_value__* napi_value;
typedef struct napi_env__* napi_env;

namespace OHOS::Ace {
#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

enum XComponentControllerErrorCode {
    XCOMPONENT_CONTROLLER_NO_ERROR = 0,
    XCOMPONENT_CONTROLLER_BAD_PARAMETER,
    XCOMPONENT_CONTROLLER_TYPE_ERROR,
    XCOMPONENT_CONTROLLER_REPEAT_SET,
    XCOMPONENT_CONTROLLER_RESET_ERROR,
};

enum class SurfaceCallbackMode : char {
    DEFAULT = 0,
    PIP,
};

/**
 * @class XComponentController
 * XComponentController interface is used to control xcomponent.
 * Xcomponent:XComponentController = 1:1
 */
class ACE_EXPORT XComponentController {
public:
    /**
     * @brief Get xcomponentController from napiValue converted by jsXComponentController
     *
     */
    static std::shared_ptr<XComponentController> GetXComponentControllerFromNapiValue(
        napi_env env, napi_value napiValue);

    /**
     * @brief set typedNode.XComponent's SurfaceCallbackMode
     *
     */
    static XComponentControllerErrorCode SetSurfaceCallbackMode(
        napi_env env, napi_value node, SurfaceCallbackMode mode);

    XComponentController() = default;
    virtual ~XComponentController() = default;

    /**
     * @brief Get xcomponent's position releated to the window in which xcomponent is located
     *
     */
    virtual XComponentControllerErrorCode GetGlobalPosition(float& offsetX, float& offsetY) = 0;

    /**
     * @brief Get xcomponent's size
     *
     */
    virtual XComponentControllerErrorCode GetSize(float& width, float& height) = 0;

    /**
     * @brief move the controling right of showing & setting size and posiotion to the other xcomponentController,
     * which cannot be repeated set more than once, unless calling reset before
     * @param xcomponentController the other xcomponentController
     */
    virtual XComponentControllerErrorCode SetExtController(
        std::shared_ptr<XComponentController> xcomponentController) = 0;

    /**
     * @brief restore the controling right of showing & setting size and posiotion from the other xcomponentController
     * which must be same as the controller set before
     * @param xcomponentController the other xcomponentController
     */
    virtual XComponentControllerErrorCode ResetExtController(
        std::shared_ptr<XComponentController> xcomponentController) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_XCOMPONENT_CONTROLLER_INTERFACE_H
