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
struct MenuAnimationDemo {
  @State message: string = '';
  @State showMenu1: boolean = false;
  @State showMenu2: boolean = false;
  @State showMenu3: boolean = false;
  @State showMenu4: boolean = false;
  scroller: Scroller = new Scroller()
  
  private menuElementList: Array<MenuElement> = [
    { value: '选项1', action: () => { this.message = '选项1 clicked'; } },
    { value: '选项2', action: () => { this.message = '选项2 clicked'; } },
    { value: '选项3', action: () => { this.message = '选项3 clicked'; } }
  ];

  @Builder
  CustomMenuBuilder() {
    Menu() {
      MenuItem({ content: '自定义选项1' })
      MenuItem({ content: '自定义选项2' })
      MenuItem({ content: '自定义选项3' })
    }
    .width(150)
    .height(120)
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('菜单动画效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 默认动画效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击切换菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.showMenu1, this.menuElementList, {
              title: '默认动画',
              placement: Placement.Bottom
            })
            .onClick(() => {
              this.showMenu1 = !this.showMenu1;
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 自定义菜单动画')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示自定义菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.CustomMenuBuilder, {
              title: '自定义菜单',
              placement: Placement.Bottom,
              borderRadius: 20
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 无动画菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('淡入淡出')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#fff3e0')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '淡入淡出',
                placement: Placement.Bottom,
                enableArrow: false
              })

            Text('缩放效果')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#fce4ec')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '缩放效果',
                placement: Placement.Bottom,
                enableArrow: false
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 菜单过渡动画')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Column({ space: 10 }) {
            Text('进入动画')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#f3e5f5')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '进入动画',
                placement: Placement.Bottom,
                enableArrow: true
              })

            Text('退出动画')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0f7fa')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '退出动画',
                placement: Placement.Bottom,
                enableArrow: true
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 快速切换菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('菜单A')
              .fontSize(14)
              .padding(15)
              .backgroundColor('#fffde7')
              .borderRadius(8)
              .bindMenu([
                {
                  value: 'A1', action: () => {
                  this.message = 'A1';
                }
                },
                {
                  value: 'A2', action: () => {
                  this.message = 'A2';
                }
                }
              ], {
                title: '菜单A',
                placement: Placement.Bottom
              })

            Text('菜单B')
              .fontSize(14)
              .padding(15)
              .backgroundColor('#efebe9')
              .borderRadius(8)
              .bindMenu([
                {
                  value: 'B1', action: () => {
                  this.message = 'B1';
                }
                },
                {
                  value: 'B2', action: () => {
                  this.message = 'B2';
                }
                }
              ], {
                title: '菜单B',
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 嵌套菜单动画')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带子菜单的菜单')
            .fontSize(14)
            .padding(15)
            .backgroundColor('#e8eaf6')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '嵌套菜单',
              placement: Placement.Bottom
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
