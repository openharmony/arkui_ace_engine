/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

const hilog = requireNapi('hilog');
const Want = requireNapi('app.ability.Want');
const componentSnapshot = requireNapi('arkui.componentSnapshot');
const componentUtils = requireNapi('arkui.componentUtils');
const image = requireNapi('multimedia.image');
const util = requireNapi('util');

const tag = 'AddFormMenuItem::js::';

async function querySnapshotAsync(want, componentId) {
  !want.parameters && (want.parameters = {});
  let pixelStr = '/9j/4AAQSk';
  let width = 300.00;
  let height = 300.00;
  let screenOffsetX = 210.00;
  let screeOffsetY = 490.00;
  want.parameters['ohos.extra.param.key.add_form_to_host_width'] = width;
  want.parameters['ohos.extra.param.key.add_form_to_host_height'] = height;
  want.parameters['ohos.extra.param.key.add_form_to_host_screenx'] = screenOffsetX;
  want.parameters['ohos.extra.param.key.add_form_to_host_screeny'] = screeOffsetY;
  want.parameters['ohos.extra.param.key.add_form_to_host_snapshot'] = pixelStr;
  hilog.info(0x3900, tag, 'pixelStr length:' + pixelStr.length);
}

function querySnapshot(want, componentId) {
  querySnapshotAsync(want, componentId);
  return true;
}

/**
 * Build function of AddFormMenuItem.
 *
 * @param { Want } want - The want of the form to publish.
 * @param { string } componentId - The id of the component used to get form snapshot.
 * @param { AddFormOptions } [options] - Add form options.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */
export function AddFormMenuItem(want, componentId, options, parent = null) {
  this.observeComponentCreation2((elmtId, isInitialRender) => {
    If.create();
    if (querySnapshot(want, componentId)) {
      this.ifElseBranchUpdateFunction(0, () => {
      });
    }
    else {
      this.ifElseBranchUpdateFunction(1, () => {
      });
    }
  }, If);
  If.pop();
  this.observeComponentCreation2((elmtId, isInitialRender) => {
    MenuItem.create(options?.style?.options ? options.style.options : {
      startIcon: {
        'id': 125830229,
        'type': 20000,
        params: ['sys.media.ic_form_menu_add'],
        'bundleName': '',
        'moduleName': ''
      },
      content: {
        'id': 125832726,
        'type': 10003,
        params: ['sys.string.ohos_add_form_to_desktop'],
        'bundleName': '',
        'moduleName': ''
      }
    });
  }, MenuItem);
  MenuItem.pop();
}

export default { AddFormMenuItem };
