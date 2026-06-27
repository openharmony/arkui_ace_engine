/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

const __dialog__ = requireInternal('arkui.dialog');

const presentDialog = function presentDialog(options) {
    return __dialog__.presentDialog(options);
};

const presentCustomDialog = function presentCustomDialog(content, options) {
    if (options === undefined) {
        return __dialog__.presentCustomDialog(content);
    }
    return __dialog__.presentCustomDialog(content, options);
};

const updateCustomDialog = function updateCustomDialog(content, options) {
    return __dialog__.updateCustomDialog(content, options);
};

const dismissDialog = function dismissDialog(target) {
    return __dialog__.dismissDialog(target);
};

export default {
    DialogController: __dialog__.DialogController,
    presentDialog,
    presentCustomDialog,
    updateCustomDialog,
    dismissDialog
};
