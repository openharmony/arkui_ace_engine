/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct MenuSwiperPage {
  list: string[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.list.push('item' + i);
    }

  }

  build() {
    Scroll() {
      Column({ space: 20 }) {

        Column() {
          Text('操作步骤：长按选中弹出菜单，滑动swiper').fontColor(Color.Blue)
          Text('Pass条件：滑动时菜单消失').fontColor(Color.Red)

          Swiper() {
            ForEach(this.list, (item: string) => {
              Text(item.toString())
                .width('90%')
                .height(160)
                .backgroundColor(0xAFEEEE)
                .textAlign(TextAlign.Center)
                .fontSize(30)
                .copyOption(CopyOptions.LocalDevice)
            }, (item: string) => item)
          }
          .displayCount(3, true)
          .itemSpace(10)
          .duration(1000)

        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)

      }.width('100%')
    }
  }
}