'use static'

/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AsyncCallback } from '@ohos.base';
import { Builder, ClickEvent, MenuItemOptions, MenuItem, $r } from '@ohos.arkui.component'
import componentSnapshot from '@ohos.arkui.componentSnapshot';
import { ComponentUtils, UIContext } from '@ohos.arkui.UIContext';
import formBindingData from '@ohos.app.form.formBindingData';
import { formMenuItem, AsyncCallbackWrapper } from './arkui.FormMenu';
import hilog from '@ohos.hilog';
import image from '@ohos.multimedia.image';
import { util } from '@kit.ArkTS';
import Want from '@ohos.app.ability.Want';

const tag = 'AddFormMenuItem::ets::';

function querySnapshot (want: Want, componentId: string): boolean {
    let uiContext = UIContext.getFocusedUIContext();
    let compInfo = uiContext?.getComponentUtils().getRectangleById(componentId);
    let imagePackageApi: image.ImagePacker = image.createImagePacker();
    try {
        let width = compInfo?.size.width.toFixed(2);
        let height = compInfo?.size.height.toFixed(2);
        let screenX = compInfo?.screenOffset.x.toFixed(2);
        let screenY = compInfo?.screenOffset.y.toFixed(2);
        !want.parameters && (want.parameters = {});
        let wantParam = want.parameters;
        if (wantParam != undefined && width != undefined && height != undefined &&
            screenX != undefined && screenY != undefined) {
            wantParam['ohos.extra.param.key.add_form_to_host_width'] = width;
            wantParam['ohos.extra.param.key.add_form_to_host_height'] = height;
            wantParam['ohos.extra.param.key.add_form_to_host_screenx'] = screenX;
            wantParam['ohos.extra.param.key.add_form_to_host_screeny'] = screenY;
        }
        const packOpts: image.PackingOption = {
            format: 'image/webp',
            quality: 50,
        };
        let packPixmap = uiContext?.getComponentSnapshot().getSync(componentId);
        if (packPixmap != undefined) {
            let arrayBuffer: ArrayBuffer = await imagePackageApi.packToData(packPixmap, packOpts);
            let base64Helper = new util.Base64Helper();
            let uint8Arr = new Uint8Array(arrayBuffer);
            let pixelStr = base64Helper.encodeToStringSync(uint8Arr);
            if (wantParam != undefined) {
                wantParam['ohos.extra.param.key.add_form_to_host_snapshot'] = pixelStr;
            }
        }
    } catch (err) {
        hilog.error(0x0000, tag, 'get pixelmap string error:' + err);
    } finally {
        imagePackageApi?.release();
    }
    return true;
}

export interface FormMenuItemStyle {
    options?: MenuItemOptions;
}

export interface AddFormOptions {
    formBindingData?: formBindingData.FormBindingData;
    callback?: AsyncCallback<string>;
    style?: FormMenuItemStyle;
}

@Builder
export function AddFormMenuItem(want: Want, componentId: string, options?: AddFormOptions): void {
    let menuItemOptions = options?.style?.options;
    if (!menuItemOptions) {
        menuItemOptions = {startIcon: $r('sys.media.ohos_ic_public_add'), content: $r('sys.string.ohos_add_form_to_desktop')}
    }
    MenuItem(menuItemOptions)
    .onClick((e: ClickEvent) => {
        querySnapshot(want, componentId);
        let formBindingData = options?.formBindingData;
        let dataStr: string = formBindingData ? JSON.stringify(formBindingData.data) : '';
        let callback = options?.callback;
        let call = callback ? new AsyncCallbackWrapper<string>(callback) : undefined;
        taskpool.execute((): void => {
            formMenuItem.requestPublishFormWithSnapshot(want, dataStr, call);
        });
    })  
}
 


