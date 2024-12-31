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

const __prompt__ = requireInternal('promptAction');

const CommonController = class CommonController {
    constructor() {};
    close() {};
};

const DialogController = class DialogController extends CommonController {
    constructor() {
        super();
        __prompt__.PromptController.bindDialog(this);
    }

    close() {
        __prompt__.PromptController.closeDialog(this);
    }
};

const showToast = function showToast(options) {
    return __prompt__.showToast(options);
};

const openToast = function openToast(options) {
    return __prompt__.openToast(options);
};

const closeToast = function closeToast(toastId) {
    return __prompt__.closeToast(toastId);
};

const showDialog = function showDialog(options, callback) {
    if (callback === undefined) {
        return __prompt__.showDialog(options);
    }
    return __prompt__.showDialog(options, callback);
};

const showActionMenu = function showActionMenu(options, callback) {
    if (callback === undefined) {
        return __prompt__.showActionMenu(options);
    }
    return __prompt__.showActionMenu(options, callback);
};

const openCustomDialog = function openCustomDialog(content, options) {
    if (options === undefined) {
        return __prompt__.openCustomDialog(content);
    }
    return __prompt__.openCustomDialog(content, options);
};

const openCustomDialogWithController = function openCustomDialogWithController(content, controller, options) {
    if (options === undefined) {
        return __prompt__.openCustomDialogWithController(content, controller);
    }
    return __prompt__.openCustomDialogWithController(content, controller, options);
};

const presentCustomDialog = function presentCustomDialog(builder, controller, options) {
    if (controller === undefined && options === undefined) {
        return __prompt__.presentCustomDialog(builder);
    }
    if (options === undefined) {
        return __prompt__.presentCustomDialog(builder, controller);
    }
    return __prompt__.presentCustomDialog(builder, controller, options);
};

const updateCustomDialog = function updateCustomDialog(content, options) {
    return __prompt__.updateCustomDialog(content, options);
};

const closeCustomDialog = function closeCustomDialog(content) {
    return __prompt__.closeCustomDialog(content);
};

export default {
    CommonController,
    DialogController,
    showToast,
    openToast,
    closeToast,
    showDialog,
    openCustomDialog,
    openCustomDialogWithController,
    presentCustomDialog,
    updateCustomDialog,
    closeCustomDialog,
    showActionMenu,
    ToastShowMode: __prompt__.ToastShowMode
};
