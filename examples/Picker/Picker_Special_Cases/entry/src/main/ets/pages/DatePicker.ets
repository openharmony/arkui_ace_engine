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

import { curves } from '@kit.ArkUI';
import { i18n } from '@kit.LocalizationKit';

interface ItemInfo {
  index: number,
  name: string,
  label: ResourceStr,
  type?: string,
}

interface ItemGroupInfo extends ItemInfo {
  children: ItemInfo[]
}

@Entry
@Component
struct DatePickerExample {
  @State isLunar: Optional<boolean> = false
  @State selectedDate: Date = new Date('1989-08-04T23:30:01')
  @State isShow: boolean = false;
  @State angle: number = 0;
  @State isVisible: boolean = true;
  @State expandedItems: Array<boolean> = []
  @State routes: Array<ItemGroupInfo> = []

  aboutToAppear(): void {
    console.log(`String : ${this.selectedDate.toString()} UTC : ${this.selectedDate.toUTCString()}
      offset : ${this.selectedDate.getTimezoneOffset()} timezone : ${Intl.DateTimeFormat()
      .resolvedOptions()
      .timeZone} timeZoneID : ${i18n.getTimeZone().getID()}`)

    for (let i = 0; i < 5; i++) {
      let child: ItemInfo = {
        name: '1',
        label: '2',
        index: 0,
      }
      let group: ItemGroupInfo = {
        name: '1',
        label: '3',
        index: i,
        children: [child, child, child, child, child]
      }
      this.routes.push(group)
      this.expandedItems.push(false)
    }
  }

  @Builder
  ListItemGroupHeader(itemGroup: ItemGroupInfo) {
    Row() {
      Text(itemGroup.label)
      Blank()
      Image($r('sys.media.ohos_ic_public_arrow_down'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(30)
        .width(30)
        .rotate({ angle: !!itemGroup.children.length ? (this.expandedItems[itemGroup.index] ? 180 : 0) : 180 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 22) })
    }
    .width('100%')
    .padding(10)
    .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
    .onTouch((event) => {
      if (event.type === TouchType.Up) {
        if (itemGroup.children.length) {
          animateTo({ curve: curves.interpolatingSpring(0, 1, 528, 39) }, () => {
            this.expandedItems[itemGroup.index] = !this.expandedItems[itemGroup.index]
          })
        }
      }
    })
  }

  build() {
    Column() {
      DatePicker({
        start: new Date(this.isLunar ? '1910-2-10' : '1910-09-01'),
        end: new Date('2024-09-08'),
        mode: DatePickerMode.DATE,
        selected: this.selectedDate
      })
        .margin({ top: 10, bottom: 10 })
        .lunar(this.isLunar)
        .canLoop(true)
        .onDateChange((value: Date) => {
          this.selectedDate = value
          console.log('onDateChange : ' + value.toString() + '\n' + this.selectedDate)
        })
        .visibility(this.isVisible ? Visibility.Visible : Visibility.None)

      Button('切换公历农历')
        .margin({ top: 30, bottom: 30 })
        .onClick(() => {
          this.isLunar = !this.isLunar
        })

      Button('DatePicker显隐')
        .margin({ top: 30, bottom: 30 })
        .onClick(() => {
          this.isVisible = !this.isVisible
        })

      Row({ space: 10 }) {
        Button('确认')
          .margin({ top: 30, bottom: 30 })
          .onClick(() => {
            this.isLunar = !this.isLunar
          })

        Button('取消')
          .margin({ top: 30, bottom: 30 })
          .onClick(() => {
            this.isLunar = !this.isLunar
          })
      }

      Column() {
        Row() {
          Text('DatePicker 出现动效测试')
            .fontSize(20)
          Blank()
          Image($r('sys.media.ohos_ic_public_arrow_down'))
            .fillColor($r('sys.color.ohos_id_color_fourth'))
            .height(30)
            .width(30)
            .rotate({ angle: this.angle })
            .animation({ curve: curves.interpolatingSpring(0, 1, 228, 22) })
        }

        Row() {
          if (this.isShow) {
            DatePicker({
              selected: new Date(),
            })
              .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
          }
        }
      }
      .height('100%')
      .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
      .onClick((event) => {
        animateTo({ curve: curves.interpolatingSpring(0, 1, 528, 39) }, () => {
          this.angle = (this.angle - 180) % 360;
          this.isShow = !this.isShow;
        })
      })
    }.width('100%')
  }
}
