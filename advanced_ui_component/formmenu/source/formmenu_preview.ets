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

import { AddFormOptions } from '@kit.ArkUI'
import { componentSnapshot, componentUtils } from '@kit.ArkUI';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { image } from '@kit.ImageKit';
import { util } from '@kit.ArkTS';
import { Want } from '@kit.AbilityKit';

const tag = 'AddFormMenuItem::ets::';

const querySnapshotAsync = async (want: Want, componentId: string): Promise<void> => {
  !want.parameters && (want.parameters = {});
  let pixelStr = '/9j/4AAQSk';
  let width = 300.00;
  let height = 300.00;
  let screenOffsetX = 210.00;
  let screeOffsetY = 490.00;
  want.parameters['ohos.extra.param.key.add_form_to_host_width'] = compInfo.size.width.toFixed(2);
  want.parameters['ohos.extra.param.key.add_form_to_host_height'] = compInfo.size.height.toFixed(2);
  want.parameters['ohos.extra.param.key.add_form_to_host_screenx'] = compInfo.screenOffset.x.toFixed(2);
  want.parameters['ohos.extra.param.key.add_form_to_host_screeny'] = compInfo.screenOffset.y.toFixed(2);
  want.parameters['ohos.extra.param.key.add_form_to_host_snapshot'] = pixelStr;
}

const querySnapshot = (want: Want, componentId: string): boolean => {
  querySnapshotAsync(want, componentId);
  return true;
}

@Builder
AddFormMenuItem(want: Want, componentId: string, options?: AddFormOptions): void {
  if (querySnapshot(want, componentId)) {
  }
  MenuItem(options?.style?.options ? options.style.options : {
    startIcon: $r('sys.media.ic_form_menu_add'),
    content: $r('sys.string.ohos_add_form_to_desktop')
  })
}