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

import display from '@ohos.display';
import { Configuration } from '@ohos.app.ability.Configuration';

/**
 * 更新px2vp、px2fp方法来适配UI尺寸
 *
 * 由于UI提供的尺寸以像素为单位，且UI图屏幕尺寸为1440x2560，所以在计算vp/fp时，需要进行转换
 *
 * 按照dpi/160 = px/vp公式，还需要对px做scale（缩放到实际屏幕尺寸）
 * 有两种计算缩放的方法，分别适配屏幕宽度和高度
 *   使用宽度计算缩放：scale = 屏幕宽度 / 1440（我们使用宽度计算）
 *   使用高度计算缩放：scale = 屏幕高度 / 2560
 * densityPixels = dpi/160 = (px*scale)/vp  --> vp = (px * scale) / densityPixels
 * ratio = scale / densityPixels            --> vp = px * ratio
 */
export function updateScale(config: Configuration) {
  let previewer = { density: 480, direction: 0, disp: { width: 1080, height: 2340, densityPixels: 3 } } // 预览配置
  let density = config ? config.screenDensity : previewer.density
  let direction = config ? config.direction : previewer.direction
  let disp = config ? display.getDefaultDisplaySync() : previewer.disp
  console.info("density:" + density + ", direction:" + direction + ", width:" + disp.width + ", height:" + disp.height)

  let scale = (direction == 0 ? disp.width : disp.height) / 720
  let ratio = scale / disp.densityPixels
  console.info("scale: " + scale + ", ratio:" + ratio)

  globalThis.px2vp = (px) => {
    return px * ratio;
  }
  globalThis.px2fp = (px) => {
    return px * ratio;
  }
}