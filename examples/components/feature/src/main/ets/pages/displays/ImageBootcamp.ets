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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled, SliderBlock, IconBlock } from 'common';

@Component
export struct ImageboxGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFocusable: boolean = true;
  @State compFocusable: boolean = true;
  @State enableCustomSize: boolean = false;
  @State customSize: string = '64*64';
  @State enableBorderRadius: boolean = false;
  @State imageBorderRadius: number = 0;
  @State enableMargin: boolean = true;
  @State compMargin: number = 0;
  @State enableImage: boolean = true;
  @State image: ResourceStr = $r('app.media.startIcon');

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Row() {
        Image(useEnabled(this.enableImage, this.image))
          .width(useEnabled(this.enableCustomSize, this.customSize.split('*')[0]))
          .height(useEnabled(this.enableCustomSize, this.customSize.split('*')[1]))
          .focusable(useEnabled(this.enableFocusable, this.compFocusable))
          .borderRadius(useEnabled(this.enableBorderRadius, this.imageBorderRadius))
          .margin(useEnabled(this.enableMargin, this.compMargin))
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        IconBlock({
          title: '是否更换图片',
          isEnabled: this.enableImage,
          icon: this.image,
        })

        RadioBlock({
          title: '图片是否走焦',
          isEnabled: this.enableFocusable,
          value: this.compFocusable,
          dataSource: [
            { label: '走焦', value: true },
            { label: '不走焦', value: false }
          ]
        })

        RadioBlock({
          title: '自定义图片尺寸',
          isEnabled: $enableCustomSize,
          value: $customSize,
          dataSource: [
            { label: '64x64', value: '64*64' },
            { label: '28x28', value: '28*28' },
            { label: '110x110', value: '110*110' }
          ]
        })

        SliderBlock({
          title: '图一圆角尺寸(vp)',
          isEnabled: $enableBorderRadius,
          value: $imageBorderRadius,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: '图片间距',
          isEnabled: $enableMargin,
          value: $compMargin,
          min: 0,
          max: 20
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ImageBootcampPreviewer {
  build() {
    ImageboxGroupBootcamp({
      title: '图片/Image'
    })
  }
}