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
struct MenuSystemMaterial {
  @State message: string = '';
  scroller: Scroller = new Scroller()

  private iconStr: Resource = $r('app.media.app_icon');

  private menuElementList: Array<MenuElement> = [
    { value: '系统材质浅色', action: () => { this.message = '系统材质浅色 clicked'; } },
    { value: '系统材质深色', action: () => { this.message = '系统材质深色 clicked'; } },
    { value: '系统材质自动', action: () => { this.message = '系统材质自动 clicked'; } }
  ];

  @Builder
  LightThemeMenuBuilder() {
    Menu() {
      MenuItem({ content: '浅色主题菜单1', startIcon: this.iconStr })
      MenuItem({ content: '浅色主题菜单2', startIcon: this.iconStr })
      MenuItem({ content: '浅色主题菜单3', startIcon: this.iconStr })
    }
    .backgroundColor('#ffffff')
    .width(180)
  }

  @Builder
  DarkThemeMenuBuilder() {
    Menu() {
      MenuItem({ content: '深色主题菜单1', startIcon: this.iconStr })
      MenuItem({ content: '深色主题菜单2', startIcon: this.iconStr })
      MenuItem({ content: '深色主题菜单3', startIcon: this.iconStr })
    }
    .backgroundColor('#1c1c1c')
    .width(180)
  }

  @Builder
  AutoThemeMenuBuilder() {
    Menu() {
      MenuItem({ content: '自动主题菜单1', startIcon: this.iconStr })
      MenuItem({ content: '自动主题菜单2', startIcon: this.iconStr })
      MenuItem({ content: '自动主题菜单3', startIcon: this.iconStr })
    }
    .width(180)
  }

  @Builder
  SystemMaterialMenu() {
    Menu() {
      MenuItem({
        content: '系统材质选项1',
        startIcon: this.iconStr
      })
      MenuItem({
        content: '系统材质选项2',
        startIcon: this.iconStr
      })
      MenuItem({
        content: '系统材质选项3',
        startIcon: this.iconStr
      })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('菜单系统材质示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 浅色主题菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('浅色背景菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.LightThemeMenuBuilder, {
              title: '浅色主题',
              placement: Placement.Bottom,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 深色主题菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('深色背景菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#37474f')
            .fontColor(Color.White)
            .borderRadius(8)
            .bindMenu(this.DarkThemeMenuBuilder, {
              title: '深色主题',
              placement: Placement.Bottom,
              enableArrow: true
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 浅色主题选项')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('文字颜色')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#ffffff')
              .fontColor('#000000')
              .borderRadius(8)
              .bindMenu([
                {
                  value: '选项1', action: () => {
                  this.message = '浅色选项1';
                }
                },
                {
                  value: '选项2', action: () => {
                  this.message = '浅色选项2';
                }
                }
              ], {
                title: '浅色文字',
                placement: Placement.Bottom
              })

            Text('深色背景')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#1c1c1c')
              .fontColor('#ffffff')
              .borderRadius(8)
              .bindMenu([
                {
                  value: '选项1', action: () => {
                  this.message = '深色选项1';
                }
                },
                {
                  value: '选项2', action: () => {
                  this.message = '深色选项2';
                }
                }
              ], {
                title: '深色背景',
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 系统材质效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('使用系统材质菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f3e5f5')
            .borderRadius(8)
            .bindMenu(this.SystemMaterialMenu, {
              title: '系统材质',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 不同尺寸菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('小')
            .fontSize(12)
            .padding(10)
            .backgroundColor('#e0f7fa')
            .borderRadius(8)
            .bindMenu(this.LightThemeMenuBuilder, {
              title: '小菜单',
              placement: Placement.Bottom
            })

          Text('中')
            .fontSize(12)
            .padding(10)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.LightThemeMenuBuilder, {
              title: '中菜单',
              placement: Placement.Bottom
            })

          Text('大')
            .fontSize(12)
            .padding(10)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindMenu(this.LightThemeMenuBuilder, {
              title: '大菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 边框和阴影效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('无边框')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e8eaf6')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '无边框',
                placement: Placement.Bottom
              })

            Text('有阴影')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e8eaf6')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '有阴影',
                placement: Placement.Bottom
              })

            Text('圆角边框')
              .fontSize(12)
              .padding(10)
              .backgroundColor('#e8eaf6')
              .borderRadius(8)
              .bindMenu(this.menuElementList, {
                title: '圆角',
                borderRadius: 20,
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
