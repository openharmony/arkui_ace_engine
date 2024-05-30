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
  let compInfo = componentUtils.getRectangleById(componentId);
  try {
    const imagePackageApi = image.createImagePacker();
    const packOpts = {
      format: 'image/jpeg',
      quality: 50,
    };
    let packPixmap = await componentSnapshot.get(componentId);
    let arrayBuffer = await imagePackageApi.packing(packPixmap, packOpts);
    let base64Helper = new util.Base64Helper();
    let uint8Arr = new Uint8Array(arrayBuffer);
    let pixelStr = base64Helper.encodeToStringSync(uint8Arr);
    !want.parameters && (want.parameters = {});
    want.parameters['ohos.extra.param.key.add_form_to_host_width'] = compInfo.size.width.toFixed(2);
    want.parameters['ohos.extra.param.key.add_form_to_host_height'] = compInfo.size.height.toFixed(2);
    want.parameters['ohos.extra.param.key.add_form_to_host_screenx'] = compInfo.screenOffset.x.toFixed(2);
    want.parameters['ohos.extra.param.key.add_form_to_host_screeny'] = compInfo.screenOffset.y.toFixed(2);
    want.parameters['ohos.extra.param.key.add_form_to_host_snapshot'] = pixelStr;
    hilog.info(0x3900, tag, 'pixelStr length:' + pixelStr.length);
  } catch (err) {
    hilog.error(0x3900, tag, 'get pixelmap string error:' + err);
  }
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
    FormMenuItem.create(options?.style?.options ? options.style.options : {
      startIcon: {
        'id': 125832775,
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
    FormMenuItem.onRegClick(want, componentId, options?.formBindingData?.data, options?.callback);
  }, FormMenuItem);
  FormMenuItem.pop();
}

export default { AddFormMenuItem };
