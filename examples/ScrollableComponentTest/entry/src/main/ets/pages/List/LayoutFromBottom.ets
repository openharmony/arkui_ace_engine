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


import { AttributeUpdater } from '@kit.ArkUI'

class MyModifier extends AttributeUpdater<ListItemAttribute> {
  applyNormalAttribute(instance: ListItemAttribute): void {
    super.applyNormalAttribute?.(instance);
  }
}

// 实现思路：在List布局完后调整ListItem的位置。最后一个ListItem底部对齐，要做到不闪烁的话，需要保证在绘制前调整ListItem的位置。可以利用onSizeChange事件，来调整ListItem的位置。
// 因为onSizeChange事件在布局完成后，绘制开始前触发。如果使用状态变量来修改ListItem的位置，会在下一帧才生效，导致闪烁，所以需要引入AttributeUpdater，绕过状态管理直接更新ListItem的
// 位置。List组件如果没有设置高度，内容不满一屏时会只适应内容，内容超过一屏会适应父组件。因此List不满一屏时插入数据，会将List撑大，回调onSizeChange事件。

@Entry
@Component
struct LayoutFromBottom {
  @State arr: number[] = [0, 1]
  private scroller: Scroller = new Scroller
  private parentHeight: number = 0
  private listHeight: number = 0
  @State itemModifier: MyModifier = new MyModifier()

  build() {
    Column() {
      Row() {
        Button('Add')
          .onClick(() => {
            this.arr.push(this.arr.length)
          })
      }

      Stack({ alignContent: Alignment.Top }) {
        List({ space: 20, initialIndex: 0, scroller: this.scroller }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .borderColor(0xFFFFFF)
            }
          }, (item: string) => item)
          ListItem() {
            Text('footer')
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .borderColor(0xFFFFFF)
          }
          .attributeModifier(this.itemModifier)
        }
        .width('90%')
        .scrollBar(BarState.Off)
        .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
          this.listHeight = newValue.height as number
          if (this.parentHeight > 0) {
            let footerY = this.parentHeight - this.listHeight;
            this.itemModifier.attribute?.translate({y: footerY})
          }
        })
        .clip(false)
      }
      .layoutWeight(1)
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.listHeight = newValue.height as number
        let footerY = this.parentHeight - this.listHeight;
        this.itemModifier.attribute?.translate({y: footerY})
      })
      .clip(true)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}