/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct MenuPlacementDemo {
  @State message: string = '';
  @State selectPlacement: Placement = Placement.Bottom;
  scroller: Scroller = new Scroller()
  
  private menuElementList: Array<MenuElement> = [
    { value: '菜单一', action: () => { this.message = '菜单一 clicked'; } },
    { value: '菜单二', action: () => { this.message = '菜单二 clicked'; } },
    { value: '菜单三', action: () => { this.message = '菜单三 clicked'; } },
    { value: '菜单四', action: () => { this.message = '菜单四 clicked'; } }
  ];

  @Builder
  MenuContent() {
    Menu() {
      MenuItem({ content: '选项1' })
      MenuItem({ content: '选项2' })
      MenuItem({ content: '选项3' })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('菜单位置放置示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. Bottom (默认)')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('菜单显示在底部')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '底部菜单',
              placement: Placement.Bottom,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. Top')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('菜单显示在顶部')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '顶部菜单',
              placement: Placement.Top,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. Left')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('菜\n单\n显\n示\n在\n左\n侧')
            .fontSize(16)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '左侧菜单',
              placement: Placement.Left,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. Right')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('菜\n单\n显\n示\n在\n右\n侧')
            .fontSize(16)
            .padding(15)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '右侧菜单',
              placement: Placement.Right,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. LeftTop')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('左上位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#f3e5f5')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '左上菜单',
              placement: Placement.LeftTop,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. RightTop')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('右上位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#e0f7fa')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '右上菜单',
              placement: Placement.RightTop,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('7. LeftBottom')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('左下位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#fffde7')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '左下菜单',
              placement: Placement.LeftBottom,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('8. RightBottom')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('右下位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#efebe9')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '右下菜单',
              placement: Placement.RightBottom,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('9. BottomLeft')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('底左位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#e8eaf6')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '底左菜单',
              placement: Placement.BottomLeft,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('10. BottomRight')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text('底右位置')
            .fontSize(16)
            .padding(20)
            .backgroundColor('#e0f2f1')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '底右菜单',
              placement: Placement.BottomRight,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        if (this.message) {
          Text(`选择: ${this.message}`)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 10 });
        }
      }
    }
  }
}
