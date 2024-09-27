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



import { ColorBlock, RadioBlock, SliderBlock } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { promptAction } from '@kit.ArkUI';

@Component
export struct BlankBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableRating: boolean = false;
  @State stars: number = 100;
  @State enableBackgroundColor: boolean = false;
  @State blankBackgroundColor: Color = 0xFF000000;
  @State blankWidth: number = 30;
  @State blankHeight: number = 30;
  @State blankMargin: number = 0;
  @State blankPadding: number = 0;
  @State enableMargin: boolean = false;
  @State enablePadding: boolean = false;
  @State marginPaddingMax: number = 5;
  @State enableControlSize: boolean = false;

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
        Text('Hello')
          .fontSize(18)
        Blank(this.blankWidth)
          .color(this.blankBackgroundColor)
          .margin(this.blankMargin)
          .padding(this.blankPadding)
          .onClick(() => {
            promptAction.showToast({
              message: '空白被点击！'
            });
          })
        Text('world')
          .fontSize(18)
      }
      .backgroundColor(0xEFEFEF)
      .borderRadius(15)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 0 }) {
        SliderBlock({
          title: '当前宽度',
          isEnabled: this.enableRating,
          value: this.blankWidth,
          min: 0,
          max: this.stars
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: this.enableBackgroundColor,
          color: this.blankBackgroundColor
        })

        SliderBlock({
          title: '当前外边距',
          isEnabled: this.enableMargin,
          value: this.blankMargin,
          min: 0,
          max: this.marginPaddingMax
        })

        SliderBlock({
          title: '当前内边距',
          isEnabled: this.enablePadding,
          value: this.blankPadding,
          min: 0,
          max: this.marginPaddingMax
        })
      }.width('100%')
    }.height('52%')
    .onDisAppear(()=>{
      AppStorage.setOrCreate('Block', []);
    })
  }
}

