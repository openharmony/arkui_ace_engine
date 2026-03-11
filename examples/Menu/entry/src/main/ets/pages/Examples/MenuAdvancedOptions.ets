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
struct MenuAdvancedOptions {
  @State selectColor: Color = Color.Blue;
  @State message: string = '';
  @State isShowMenu: boolean = false;
  scroller: Scroller = new Scroller()
  
  private iconStr: Resource = $r('app.media.app_icon');

  private menuElementList: Array<MenuElement> = [
    {
      value: '复制',
      icon: $r('app.media.app_icon'),
      action: () => {
        this.message = '复制 clicked';
        console.info('Menu copy clicked');
      }
    },
    {
      value: '粘贴',
      icon: $r('app.media.app_icon'),
      action: () => {
        this.message = '粘贴 clicked';
        console.info('Menu paste clicked');
      }
    },
    {
      value: '剪切',
      icon: $r('app.media.app_icon'),
      action: () => {
        this.message = '剪切 clicked';
        console.info('Menu cut clicked');
      }
    },
    {
      value: '全选',
      icon: $r('app.media.app_icon'),
      action: () => {
        this.message = '全选 clicked';
        console.info('Menu select all clicked');
      }
    }
  ];

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项1' })
        .onClick(() => {
          this.message = '菜单选项1 clicked';
        })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项2' })
        .onClick(() => {
          this.message = '菜单选项2 clicked';
        })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项3' })
        .onClick(() => {
          this.message = '菜单选项3 clicked';
        })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('Menu高级选项配置示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 基本菜单选项')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f0f0f0')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '编辑选项',
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 自定义菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示自定义菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e0f0e0')
            .borderRadius(8)
            .bindMenu(this.MyMenu, {
              title: '自定义菜单',
              enableArrow: true,
              borderRadius: 20,
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 禁用箭头菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('无箭头菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f0e0f0')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '禁用箭头',
              enableArrow: false,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 不同位置的菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('Top')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuElementList, {
                title: '上方菜单',
                placement: Placement.Top
              })

            Text('Left')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuElementList, {
                title: '左侧菜单',
                placement: Placement.Left
              })

            Text('Right')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuElementList, {
                title: '右侧菜单',
                placement: Placement.Right
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 带偏移的菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带偏移的菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffe0e0')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '偏移菜单',
              offset: { x: 20, y: 10 },
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 带圆角的菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('大圆角菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e0ffe0')
            .borderRadius(8)
            .bindMenu(this.menuElementList, {
              title: '圆角菜单',
              borderRadius: 30,
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
