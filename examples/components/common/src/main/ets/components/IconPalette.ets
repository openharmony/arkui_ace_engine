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
import { BlockTag } from '../model/BlockTag';
import { tagDesRule } from '../utils';
import { formatDate } from '../utils/timeUtil';

@Component
export struct IconPalette {
  @Prop icon: ResourceStr | undefined = undefined;
  @Prop icons: ResourceStr[] = [
    $r('sys.media.ohos_ic_public_device_phone'),
    $r('sys.media.ohos_ic_public_device_pad'),
    $r('sys.media.ohos_ic_public_device_smartscreen'),
    $r('sys.media.ohos_ic_public_device_matebook'),
    $r('sys.media.ohos_ic_public_device_watch'),
    $r('sys.media.ohos_ic_public_device_soundx_filled'),
  ];
  @Prop isEnabled: boolean = false;
  @Prop title: string = '';
  onChange?: (color: ResourceStr, index: number) => void;

  private equals(icon1: ResourceStr, icon2: ResourceStr) {
    const type1 = typeof icon1;
    const type2 = typeof icon2;
    if (type1 !== type2) {
      return false;
    }

    if (type1 === 'object') {
      return (icon1 as Resource).id === (icon2 as Resource).id;
    }

    return icon1 === icon2;
  }

  build() {
    Row({ space: 12 }) {
      ForEach(this.icons, (icon: ResourceStr, index: number) => {
        Button() {
          Image(icon)
            .size({ width: 24, height: 24 })
            .fillColor(this.equals(icon, this.icon) ? $r('sys.color.ohos_id_color_emphasize') :
            $r('sys.color.ohos_id_color_text_secondary'))
            .animation({ curve: Curve.Sharp, duration: 150 })
        }
        .type(ButtonType.Circle)
        .backgroundColor(Color.Transparent)
        .width(32)
        .height(32)
        .enabled(this.isEnabled)
        .onClick(() => {
          this.onChange?.(icon, index);
        })
      })
    }
    .width('100%')
    .grayscale(this.isEnabled ? 0 : 1)
  }
}

@Preview
@Component
struct IconPalettePreview {
  build() {
    IconPalette({})
  }
}