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

import Want from '@ohos.app.ability.Want';
import hilog from '@ohos.hilog';
import componentSnapshot from '@ohos.arkui.componentSnapshot';
import componentUtils from '@ohos.arkui.componentUtils';
import image from '@ohos.multimedia.image';
import util from '@ohos.util';
import { AsyncCallback, BusinessError } from '@ohos.base';
import formBindingData from '@ohos.app.form.formBindingData';

export interface FormMenuItemStyle {
  /**
   * Defines options of the form menu.
   *
   * @type { ?MenuItemOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 12
   */
  options?: MenuItemOptions;
}

/**
 * Defines the add form options.
 *
 * @interface AddFormOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */
export interface AddFormOptions {
  /**
   * Indicates the form data.
   *
   * @type { ?formBindingData.FormBindingData }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 12
   */
  formBindingData?: formBindingData.FormBindingData;

  /**
   * The callback is used to return the form id.
   *
   * @type { ?AsyncCallback<string> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 12
   */
  callback?: AsyncCallback<string>;

  /**
   * The style of the menu item.
   *
   * @type { ?FormMenuItemStyle }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 12
   */
  style?: FormMenuItemStyle;
}

const tag = 'AddFormMenuItem::ets::';

async function querySnapshot(want: Want, componentId: string){
  let compInfo = componentUtils.getRectangleById(componentId);
  try {
    const imagePackageApi: image.ImagePacker = image.createImagePacker();
    const packOpts: image.PackingOption = {
      format: 'image/jpeg',
      quality: 100,
    };
    let packPixmap: image.PixelMap = await componentSnapshot.get(componentId);
    let arrayBuffer: ArrayBuffer = await imagePackageApi.packing(packPixmap, packOpts);
    let base64Helper = new util.Base64Helper();
    let uint8Arr = new Uint8Array(arrayBuffer);
    let pixelStr = base64Helper.encodeToStringSync(uint8Arr);
    !want.parameters && (want.parameters = {});
    want.parameters['ohos.extra.param.key.add_form_to_host_snapshot'] = pixelStr;
    want.parameters['ohos.extra.param.key.add_form_to_host_width'] = compInfo.size.width;
    want.parameters['ohos.extra.param.key.add_form_to_host_height'] = compInfo.size.height;
    want.parameters['ohos.extra.param.key.add_form_to_host_screenx'] = compInfo.screenOffset.x;
    want.parameters['ohos.extra.param.key.add_form_to_host_screeny'] = compInfo.screenOffset.y;
  } catch (err) {
    hilog.error(0x3900, tag, 'get pixelmap string error:' + err);
  }
}

@Builder
export function AddFormMenuItem(want: Want, componentId: string, options?: AddFormOptions): void{
  FormMenuItem(options?.style?.options ? options.style.options : {
    startIcon: $r('sys.media.ohos_ic_public_add'),
    content: $r('sys.string.ohos_add_form_to_desktop')
  })
    .onAppear(async () => {
      await querySnapshot(want, componentId);
    })
    .onClick(() => { }, want, componentId, options?.formBindingData, options?.callback
    );
}