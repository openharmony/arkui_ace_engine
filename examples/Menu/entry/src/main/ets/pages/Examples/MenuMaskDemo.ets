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
struct MenuMaskDemo {
  @State message: string = '';
  scroller: Scroller = new Scroller()
  
  private iconStr: Resource = $r('app.media.app_icon');

  private menuElementList: Array<MenuElement> = [
    { value: '选项1', action: () => { this.message = '选项1 clicked'; } },
    { value: '选项2', action: () => { this.message = '选项2 clicked'; } },
    { value: '选项3', action: () => { this.message = '选项3 clicked'; } }
  ];

  @Builder
  MenuContentBuilder() {
    Menu() {
      MenuItem({ content: '菜单选项1', startIcon: this.iconStr })
      MenuItem({ content: '菜单选项2', startIcon: this.iconStr })
      MenuItem({ content: '菜单选项3', startIcon: this.iconStr })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('菜单遮罩效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 无遮罩菜单 (默认)')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示无遮罩菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '无遮罩菜单',
              mask: false,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 有遮罩菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示有遮罩菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '有遮罩菜单',
              mask: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 自定义菜单带遮罩')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示自定义菜单(有遮罩)')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.MenuContentBuilder, {
              title: '自定义遮罩菜单',
              mask: true,
              borderRadius: 20,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 上下文菜单遮罩效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示有遮罩菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindContextMenu(this.MenuContentBuilder, ResponseType.LongPress, {
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 上下文菜单无遮罩')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示无遮罩菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f3e5f5')
            .borderRadius(8)
            .bindContextMenu(this.MenuContentBuilder, ResponseType.LongPress, {
              preview: MenuPreviewMode.NONE,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 位置与遮罩组合')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('上方+遮罩')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e0f7fa')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '上方遮罩',
                mask: true,
                placement: Placement.Top
              })

            Text('下方+遮罩')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#fffde7')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '下方遮罩',
                mask: true,
                placement: Placement.Bottom
              })

            Text('左侧+遮罩')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#efebe9')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '左侧遮罩',
                mask: true,
                placement: Placement.Left
              })

            Text('右侧+遮罩')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e8eaf6')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '右侧遮罩',
                mask: true,
                placement: Placement.Right
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('7. 不同圆角与遮罩')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('小圆角')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e1f5fe')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '小圆角遮罩',
                mask: true,
                borderRadius: 5,
                placement: Placement.Bottom
              })

            Text('中圆角')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e8f5e9')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '中圆角遮罩',
                mask: true,
                borderRadius: 15,
                placement: Placement.Bottom
              })

            Text('大圆角')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#fff3e0')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '大圆角遮罩',
                mask: true,
                borderRadius: 30,
                placement: Placement.Bottom
              })
          }
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
