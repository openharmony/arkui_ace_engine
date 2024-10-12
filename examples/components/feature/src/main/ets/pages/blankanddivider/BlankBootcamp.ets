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


import { ColorBlock, SliderBlock, useEnabled } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { promptAction } from '@kit.ArkUI';

@Component
export struct BlankBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableBackgroundColor: boolean = false;
  @State blankBackgroundColor: Color = 0xFF000000;
  @State blankWidth: number = 20;
  @State enableBlankWidth: boolean = false;
  @State blankHeight: number = 20;
  @State enableBlankHeight: boolean = false;
  @State blankMargin: number = 0;
  @State enableBlankMargin: boolean = false;
  @State blankPadding: number = 0;
  @State enableBlankPadding: boolean = false;

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
    Row() {
      Text('Hello')
      Blank()
        .color(useEnabled(this.enableBackgroundColor, this.blankBackgroundColor))
        .margin(useEnabled(this.enableBlankMargin, this.blankMargin))
        .padding(useEnabled(this.enableBlankPadding, this.blankPadding))
        .width(useEnabled(this.enableBlankWidth, this.blankWidth))
        .height(useEnabled(this.enableBlankHeight, this.blankHeight))
      Toggle({ type: ToggleType.Switch })
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column() {
        SliderBlock({
          title: '宽度',
          isEnabled: $enableBlankWidth,
          value: $blankWidth,
          min: 10,
          max: 100
        })

        SliderBlock({
          title: '高度',
          isEnabled: $enableBlankHeight,
          value: $blankHeight,
          min: 10,
          max: 100
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableBackgroundColor,
          color: $blankBackgroundColor
        })

        SliderBlock({
          title: '当前外边距',
          isEnabled: $enableBlankMargin,
          value: $blankMargin,
          min: 0,
          max: 5
        })

        SliderBlock({
          title: '当前内边距',
          isEnabled: $enableBlankPadding,
          value: $blankPadding,
          min: 0,
          max: 5
        })
      }.width('100%')
    }.height('52%')
  }
}

@Preview
@Component
struct BlankBootcampPreviewer {
  build() {
    BlankBootcamp({
      title: '空白/blank'
    })
  }
}

