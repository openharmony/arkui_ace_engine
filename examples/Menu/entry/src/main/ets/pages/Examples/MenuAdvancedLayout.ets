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

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct MenuAdvancedLayout {
  @State currentPlacement: Placement = Placement.Bottom
  @State enableArrow: boolean = true
  @State arrowOffset: number = 0
  @State menuOffset: Position = { x: 0, y: 0 }
  @State showInSubWindow: boolean = false
  @State eventLog: string = ''
  @State currentRadius: Length = 16
  @State layoutRegionMargin: Margin | undefined = undefined
  @State enableHoverMode: boolean = false

  private iconResource: Resource = $r('app.media.app_icon')

  @Builder
  PlacementMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '位置设置菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '选项1'
        })
          .onClick(() => {
            this.addLog('点击: 选项1')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '选项2'
        })
          .onClick(() => {
            this.addLog('点击: 选项2')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '选项3'
        })
          .onClick(() => {
            this.addLog('点击: 选项3')
          })
      }
    }
  }

  @Builder
  ArrowMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '箭头设置菜单' }) {
        MenuItem({ content: '功能A' })
        MenuItem({ content: '功能B' })
        MenuItem({ content: '功能C' })
      }
    }
  }

  @Builder
  SideSubMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件操作', builder: (): void => this.FileSubMenu() })
      MenuItem({ content: '编辑操作', builder: (): void => this.EditSubMenu() })
      MenuItem({ content: '视图操作', builder: (): void => this.ViewSubMenu() })
    }
  }

  @Builder
  EmbeddedSubMenuBuilder() {
    Menu() {
      MenuItem({ content: '工具', builder: (): void => this.ToolsSubMenu() })
      MenuItem({ content: '设置', builder: (): void => this.SettingsSubMenu() })
      MenuItem({ content: '帮助', builder: (): void => this.HelpSubMenu() })
    }
  }

  @Builder
  StackSubMenuBuilder() {
    Menu() {
      MenuItem({ content: '导航', builder: (): void => this.NavigationSubMenu() })
      MenuItem({ content: '搜索', builder: (): void => this.SearchSubMenu() })
      MenuItem({ content: '分享', builder: (): void => this.ShareSubMenu() })
    }
  }

  @Builder
  FileSubMenu() {
    Menu() {
      MenuItem({ content: '新建', labelInfo: 'Ctrl+N' })
      MenuItem({ content: '打开', labelInfo: 'Ctrl+O' })
      MenuItem({ content: '保存', labelInfo: 'Ctrl+S' })
      MenuItem({ content: '另存为', labelInfo: 'Ctrl+Shift+S' })
    }
  }

  @Builder
  EditSubMenu() {
    Menu() {
      MenuItem({ content: '撤销', labelInfo: 'Ctrl+Z' })
      MenuItem({ content: '重做', labelInfo: 'Ctrl+Y' })
      MenuItem({ content: '剪切', labelInfo: 'Ctrl+X' })
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  ViewSubMenu() {
    Menu() {
      MenuItem({ content: '放大', labelInfo: 'Ctrl++' })
      MenuItem({ content: '缩小', labelInfo: 'Ctrl+-' })
      MenuItem({ content: '重置缩放', labelInfo: 'Ctrl+0' })
      MenuItem({ content: '全屏', labelInfo: 'F11' })
    }
  }

  @Builder
  ToolsSubMenu() {
    Menu() {
      MenuItem({ content: '查找', labelInfo: 'Ctrl+F' })
      MenuItem({ content: '替换', labelInfo: 'Ctrl+H' })
      MenuItem({ content: '转到行', labelInfo: 'Ctrl+G' })
    }
  }

  @Builder
  SettingsSubMenu() {
    Menu() {
      MenuItem({ content: '首选项' })
      MenuItem({ content: '键盘快捷键' })
      MenuItem({ content: '主题设置' })
      MenuItem({ content: '语言设置' })
    }
  }

  @Builder
  HelpSubMenu() {
    Menu() {
      MenuItem({ content: '文档' })
      MenuItem({ content: '教程' })
      MenuItem({ content: '关于' })
    }
  }

  @Builder
  NavigationSubMenu() {
    Menu() {
      MenuItem({ content: '首页' })
      MenuItem({ content: '上一页' })
      MenuItem({ content: '下一页' })
      MenuItem({ content: '末页' })
    }
  }

  @Builder
  SearchSubMenu() {
    Menu() {
      MenuItem({ content: '搜索页面' })
      MenuItem({ content: '高级搜索' })
      MenuItem({ content: '搜索历史' })
    }
  }

  @Builder
  ShareSubMenu() {
    Menu() {
      MenuItem({ content: '分享到微信' })
      MenuItem({ content: '分享到微博' })
      MenuItem({ content: '复制链接' })
    }
  }

  @Builder
  ComplexGroupMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '常用操作' }) {
        MenuItem({ startIcon: this.iconResource, content: '新建' })
        MenuItem({ startIcon: this.iconResource, content: '打开' })
        MenuItem({ startIcon: this.iconResource, content: '保存' })
      }
      MenuItemGroup({ header: '编辑操作' }) {
        MenuItem({ startIcon: this.iconResource, content: '复制' })
        MenuItem({ startIcon: this.iconResource, content: '粘贴' })
        MenuItem({ startIcon: this.iconResource, content: '删除' })
      }
      MenuItemGroup({ header: '高级功能' }) {
        MenuItem({ startIcon: this.iconResource, content: '导出' })
        MenuItem({ startIcon: this.iconResource, content: '导入' })
        MenuItem({ startIcon: this.iconResource, content: '同步' })
      }
    }
  }

  @Builder
  CustomLayoutMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '布局选项' }) {
        MenuItem({ content: '网格布局' })
        MenuItem({ content: '列表布局' })
        MenuItem({ content: '卡片布局' })
      }
      MenuItemGroup({ header: '排序方式' }) {
        MenuItem({ content: '按名称' })
        MenuItem({ content: '按日期' })
        MenuItem({ content: '按大小' })
      }
      MenuItemGroup({ header: '显示选项' }) {
        MenuItem({ content: '显示隐藏文件' })
        MenuItem({ content: '显示缩略图' })
        MenuItem({ content: '显示详情' })
      }
    }
  }

  addLog(message: string): void {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog = `[${timestamp}] ${message}\n${this.eventLog}`
  }

  build() {
    Column() {
      Scroll() {
        Column({ space: 20 }) {
          Text('高级菜单布局示例')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Column({ space: 15 }) {
            Text('菜单位置设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('当前位置:')
                .fontSize(14)
                .width(80)
              Text(`${this.currentPlacement}`)
                .fontSize(14)
                .fontColor('#2196F3')
                .layoutWeight(1)
            }
            .width('100%')

            Grid() {
              GridItem() {
                Button('Top')
                  .width(60)
                  .height(35)
                  .fontSize(12)
                  .type(this.currentPlacement === Placement.Top ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentPlacement === Placement.Top ? '#2196F3' : '#E0E0E0')
                  .fontColor(this.currentPlacement === Placement.Top ? '#FFFFFF' : '#000000')
                  .onClick(() => {
                    this.currentPlacement = Placement.Top
                  })
              }
              GridItem() {
                Button('Bottom')
                  .width(60)
                  .height(35)
                  .fontSize(12)
                  .type(this.currentPlacement === Placement.Bottom ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentPlacement === Placement.Bottom ? '#2196F3' : '#E0E0E0')
                  .fontColor(this.currentPlacement === Placement.Bottom ? '#FFFFFF' : '#000000')
                  .onClick(() => {
                    this.currentPlacement = Placement.Bottom
                  })
              }
              GridItem() {
                Button('Left')
                  .width(60)
                  .height(35)
                  .fontSize(12)
                  .type(this.currentPlacement === Placement.Left ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentPlacement === Placement.Left ? '#2196F3' : '#E0E0E0')
                  .fontColor(this.currentPlacement === Placement.Left ? '#FFFFFF' : '#000000')
                  .onClick(() => {
                    this.currentPlacement = Placement.Left
                  })
              }
              GridItem() {
                Button('Right')
                  .width(60)
                  .height(35)
                  .fontSize(12)
                  .type(this.currentPlacement === Placement.Right ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentPlacement === Placement.Right ? '#2196F3' : '#E0E0E0')
                  .fontColor(this.currentPlacement === Placement.Right ? '#FFFFFF' : '#000000')
                  .onClick(() => {
                    this.currentPlacement = Placement.Right
                  })
              }
              GridItem() {
                Button('TopLeft')
                  .width(70)
                  .height(35)
                  .fontSize(12)
                  .onClick(() => {
                    this.currentPlacement = Placement.TopLeft
                  })
              }
              GridItem() {
                Button('TopRight')
                  .width(70)
                  .height(35)
                  .fontSize(12)
                  .onClick(() => {
                    this.currentPlacement = Placement.TopRight
                  })
              }
              GridItem() {
                Button('BottomLeft')
                  .width(80)
                  .height(35)
                  .fontSize(12)
                  .onClick(() => {
                    this.currentPlacement = Placement.BottomLeft
                  })
              }
              GridItem() {
                Button('BottomRight')
                  .width(80)
                  .height(35)
                  .fontSize(12)
                  .onClick(() => {
                    this.currentPlacement = Placement.BottomRight
                  })
              }
            }
            .columnsTemplate('1fr 1fr 1fr 1fr')
            .rowsTemplate('1fr 1fr')
            .width('100%')
            .height(80)

            Button('显示位置菜单')
              .fontSize(16)
              .width(150)
              .height(45)
              .backgroundColor('#4CAF50')
              .bindMenu(this.PlacementMenuBuilder)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('箭头设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('显示箭头:')
                .fontSize(14)
                .width(80)
              Toggle({ type: ToggleType.Switch, isOn: this.enableArrow })
                .onChange((isOn: boolean) => {
                  this.enableArrow = isOn
                })
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('箭头偏移:')
                .fontSize(14)
                .width(80)
              Slider({
                min: -50,
                max: 50,
                value: this.arrowOffset,
                step: 1
              })
                .width('50%')
                .onChange((value: number) => {
                  this.arrowOffset = value
                })
              Text(`${this.arrowOffset}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Button('显示箭头菜单')
              .fontSize(16)
              .width(150)
              .height(45)
              .backgroundColor('#FF9800')
              .bindMenu(this.ArrowMenuBuilder)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)
        }
        .width('100%')
        .padding({ left: 15, right: 15 })
      }
      .width('100%')
      .height('100%')
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F0F0')
  }
}
