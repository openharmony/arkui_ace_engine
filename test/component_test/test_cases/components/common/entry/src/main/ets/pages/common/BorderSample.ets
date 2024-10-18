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

import borderTest from '../MyTest/BorderTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderSample {
  borderArr: BorderOptions[] = [{
    width: 10,
    color: Color.Black,
    radius: 30,
    style: BorderStyle.Solid
  },
    {
      width: '10px',
      color: '#e3bbbb',
      radius: '50px',
      style: BorderStyle.Dotted
    },
    {
      width: {
        left: '10px',
        right: '20px',
        top: '30px',
        bottom: '40px'
      },
      color: {
        left: '#e3bbbb',
        right: '#ff0000',
        top: '#00ff00',
        bottom: '#0000ff'
      },
      radius: {
        topLeft: '50px',
        topRight: '70px',
        bottomLeft: '90px',
        bottomRight: '110px'
      },
      style: {
        left: BorderStyle.Dotted,
        right: BorderStyle.Dotted,
        top: BorderStyle.Solid,
        bottom: BorderStyle.Dashed
      }
    }]

  aboutToAppear(): void {
    loadComponentTestEntry(borderTest)
  }

  index: number = 0
  @State value: BorderOptions = this.borderArr[this.index]

  build() {
    Column({ space: 5 }) {
      Row()
        .width(50)
        .height(50)
        .id('rowBorder1')
        .border(this.value)
      Button('ButtonBorder')
        .onClick(() => {
          this.index++
          this.value = this.borderArr[this.index % 3]
        })
      TextInput()
        .height('10%')
        .id('textInputBorder')
        .border({
          width: $r('app.string.common_width'),
          color: $r('sys.color.ohos_id_color_button_normal'),
          radius: $r('app.string.common_radius'),
          style: BorderStyle.Dashed
        })
      Row()
        .width(50)
        .height(50)
        .id('rowBorder2')
        .border({
          width: {
            left: 3,
            right: 6,
            top: 10,
            bottom: 15
          },
          color: {
            left: 0x0000ff,
            right: 0xff0000,
            top: 0x00ff00,
            bottom: 0x0000ff
          },
          radius: {
            topLeft: 10,
            topRight: 20,
            bottomLeft: 40,
            bottomRight: 80
          },
          style: {
            left: BorderStyle.Dotted,
            right: BorderStyle.Dotted,
            top: BorderStyle.Solid,
            bottom: BorderStyle.Dashed
          }
        })
      Menu()
        .width(50)
        .height(50)
        .id('menuBorder')
        .border({
          width: {
            left: $r('app.string.commonPosition_length'),
            right: $r('app.string.commonPosition_length'),
            top: $r('app.string.commonPosition_length'),
            bottom: $r('app.string.commonPosition_length')
          },
          color: {
            left: $r('sys.color.ohos_id_radio_shadow_color'),
            right: $r('sys.color.ohos_toggle_bg_transparent'),
            top: $r('sys.color.ohos_id_toolbar_item_focus_color'),
            bottom: $r('sys.color.ohos_fa_emphasize_outline')
          },
          radius: {
            topLeft: $r('app.string.commonPosition_length'),
            topRight: $r('app.string.commonPosition_length'),
            bottomLeft: $r('app.string.commonPosition_length'),
            bottomRight: $r('app.string.commonPosition_length')
          },
          style: {
            left: BorderStyle.Dotted,
            right: BorderStyle.Dotted,
            top: BorderStyle.Solid,
            bottom: BorderStyle.Dashed
          }
        })
    }
  }
}

