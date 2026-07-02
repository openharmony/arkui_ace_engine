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

const DialogBaseController = class DialogBaseController {
    constructor() {
        __dialog__.DialogController.bindDialog(this);
    }

    close() {
        __dialog__.DialogController.closeDialog(this);
    }

    getState() {
        return __dialog__.DialogController.getState(this);
    }
};

let DialogBaseAlignment;
(function (DialogBaseAlignment) {
  DialogBaseAlignment[DialogBaseAlignment.TOP = 0] = 'TOP';
  DialogBaseAlignment[DialogBaseAlignment.CENTER = 1] = 'CENTER';
  DialogBaseAlignment[DialogBaseAlignment.BOTTOM = 2] = 'BOTTOM';
  DialogBaseAlignment[DialogBaseAlignment.DEFAULT = 3] = 'DEFAULT';
  DialogBaseAlignment[DialogBaseAlignment.TOP_START = 4] = 'TOP_START';
  DialogBaseAlignment[DialogBaseAlignment.TOP_END = 5] = 'TOP_END';
  DialogBaseAlignment[DialogBaseAlignment.CENTER_START = 6] = 'CENTER_START';
  DialogBaseAlignment[DialogBaseAlignment.CENTER_END = 7] = 'CENTER_END';
  DialogBaseAlignment[DialogBaseAlignment.BOTTOM_START = 8] = 'BOTTOM_START';
  DialogBaseAlignment[DialogBaseAlignment.BOTTOM_END = 9] = 'BOTTOM_END';
})(DialogBaseAlignment || (DialogBaseAlignment = {}));

let DialogButtonOrientation;
(function (DialogButtonOrientation) {
  DialogButtonOrientation[DialogButtonOrientation.AUTO = 0] = 'AUTO';
  DialogButtonOrientation[DialogButtonOrientation.HORIZONTAL = 1] = 'HORIZONTAL';
  DialogButtonOrientation[DialogButtonOrientation.VERTICAL = 2] = 'VERTICAL';
})(DialogButtonOrientation || (DialogButtonOrientation = {}));

let DialogState;
(function (DialogState) {
    DialogState[DialogState.UNINITIALIZED = 0] = 'UNINITIALIZED';
    DialogState[DialogState.INITIALIZED = 1] = 'INITIALIZED';
    DialogState[DialogState.APPEARING = 2] = 'APPEARING';
    DialogState[DialogState.APPEARED = 3] = 'APPEARED';
    DialogState[DialogState.DISAPPEARING = 4] = 'DISAPPEARING';
    DialogState[DialogState.DISAPPEARED = 5] = 'DISAPPEARED';
})(DialogState || (DialogState = {}));

export default {
    DialogBaseController,
    presentDialog,
    presentCustomDialog,
    updateCustomDialog,
    dismissDialog,
    DialogBaseAlignment,
    DialogButtonOrientation,
    DialogState
};
