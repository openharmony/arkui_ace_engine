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
  let pixelStr = '/9j/4AAQSkZJRgABAQAAAQABAAD/4gIoSUNDX1BST0ZJTEUAAQEAAAIYAAAAAAQwAABtbnRyUkdCIFhZWiAAAAAAAAAAAAAAAABhY3NwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA9tYAAQAAAADTLQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAlkZXNjAAAA8AAAAHRyWFlaAAABZAAAABRnWFlaAAABeAAAABRiWFlaAAABjAAAABRyVFJDAAABoAAAAChnVFJDAAABoAAAAChiVFJDAAABoAAAACh3dHB0AAAByAAAABRjcHJ0AAAB3AAAADxtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAFgAAAAcAHMAUgBHAEIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAABvogAAOPUAAAOQWFlaIAAAAAAAAGKZAAC3hQAAGNpYWVogAAAAAAAAJKAAAA + EAAC2z3BhcmEAAAAAAAQAAAACZmYAAPKnAAANWQAAE9AAAApbAAAAAAAAAABYWVogAAAAAAAA9tYAAQAAAADTLW1sdWMAAAAAAAAAAQAAAAxlblVTAAAAIAAAABwARwBvAG8AZwBsAGUAIABJAG4AYwAuACAAMgAwADEANv / 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';
  let width = 300.00
  let height = 300.00
  let screenOffsetX = 210.00
  let screeOffsetY = 490.00
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
