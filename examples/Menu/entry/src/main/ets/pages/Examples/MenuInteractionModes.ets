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

import { SymbolGlyphModifier } from '@kit.ArkUI';

@Entry
@Component
struct MenuInteractionModes {
  @State clickMenuVisible: boolean = false
  @State longPressMenuVisible: boolean = false
  @State rightClickMenuVisible: boolean = false
  @State isShowMenu: boolean = false
  @State eventLog: string = ''
  @State lastInteractionType: string = ''
  @State pressStartTime: number = 0
  @State menuShowCount: number = 0
  @State lastMenuCloseTime: string = ''

  private iconResource: Resource = $r('app.media.app_icon')

  @Builder
  ClickInteractionMenu() {
    Menu() {
      MenuItemGroup({ header: '点击交互菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '新建文档'
        })
          .onClick(() => {
            this.addLog('点击交互 - 新建文档')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '打开文档'
        })
          .onClick(() => {
            this.addLog('点击交互 - 打开文档')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '保存文档'
        })
          .onClick(() => {
            this.addLog('点击交互 - 保存文档')
          })
      }
      MenuItemGroup({ header: '高级选项' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '导出为PDF'
        })
          .onClick(() => {
            this.addLog('点击交互 - 导出为PDF')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '打印文档'
        })
          .onClick(() => {
            this.addLog('点击交互 - 打印文档')
          })
      }
    }
    .onAppear(() => {
      this.menuShowCount++
      this.lastInteractionType = '点击'
      this.addLog('点击菜单已显示')
    })
  }

  @Builder
  LongPressInteractionMenu() {
    Menu() {
      MenuItemGroup({ header: '长按交互菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '复制'
        })
          .onClick(() => {
            this.addLog('长按交互 - 复制')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '剪切'
        })
          .onClick(() => {
            this.addLog('长按交互 - 剪切')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '粘贴'
        })
          .onClick(() => {
            this.addLog('长按交互 - 粘贴')
          })
      }
      MenuItemGroup({ header: '选择操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '全选'
        })
          .onClick(() => {
            this.addLog('长按交互 - 全选')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '取消选择'
        })
          .onClick(() => {
            this.addLog('长按交互 - 取消选择')
          })
      }
    }
    .onAppear(() => {
      this.menuShowCount++
      this.lastInteractionType = '长按'
      this.addLog('长按菜单已显示')
    })
  }

  @Builder
  RightClickInteractionMenu() {
    Menu() {
      MenuItemGroup({ header: '右键交互菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '刷新页面'
        })
          .onClick(() => {
            this.addLog('右键交互 - 刷新页面')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '查看源代码'
        })
          .onClick(() => {
            this.addLog('右键交互 - 查看源代码')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '检查元素'
        })
          .onClick(() => {
            this.addLog('右键交互 - 检查元素')
          })
      }
      MenuItemGroup({ header: '页面操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '后退'
        })
          .onClick(() => {
            this.addLog('右键交互 - 后退')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '前进'
        })
          .onClick(() => {
            this.addLog('右键交互 - 前进')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '保存页面'
        })
          .onClick(() => {
            this.addLog('右键交互 - 保存页面')
          })
      }
    }
    .onAppear(() => {
      this.menuShowCount++
      this.lastInteractionType = '右键'
      this.addLog('右键菜单已显示')
    })
  }

  @Builder
  StateControlledMenu() {
    Menu() {
      MenuItemGroup({ header: '状态控制菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '选项A'
        })
          .onClick(() => {
            this.addLog('状态控制菜单 - 选项A')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '选项B'
        })
          .onClick(() => {
            this.addLog('状态控制菜单 - 选项B')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '选项C'
        })
          .onClick(() => {
            this.addLog('状态控制菜单 - 选项C')
          })
      }
    }
    .onAppear(() => {
      this.addLog('状态控制菜单已显示')
    })
  }

  @Builder
  MixedInteractionMenu() {
    Menu() {
      MenuItemGroup({ header: '混合交互菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '功能1'
        })
          .onClick(() => {
            this.addLog('混合交互 - 功能1')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '功能2'
        })
          .onClick(() => {
            this.addLog('混合交互 - 功能2')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '功能3'
        })
          .onClick(() => {
            this.addLog('混合交互 - 功能3')
          })
      }
      MenuItemGroup({ header: '设置选项' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '偏好设置'
        })
          .onClick(() => {
            this.addLog('混合交互 - 偏好设置')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '帮助文档'
        })
          .onClick(() => {
            this.addLog('混合交互 - 帮助文档')
          })
      }
    }
  }

  @Builder
  HapticFeedbackMenu() {
    Menu() {
      MenuItemGroup({ header: '触觉反馈菜单' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '震动选项1'
        })
        MenuItem({
          startIcon: this.iconResource,
          content: '震动选项2'
        })
        MenuItem({
          startIcon: this.iconResource,
          content: '震动选项3'
        })
      }
    }
  }

  @Builder
  PreviewMenu() {
    Menu() {
      MenuItem({ content: '预览选项1' })
      MenuItem({ content: '预览选项2' })
      MenuItem({ content: '预览选项3' })
    }
  }

  @Builder
  PreviewBuilder() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(120)
        .height(80)
        .borderRadius(8)
      Text('预览内容')
        .fontSize(14)
        .margin({ top: 5 })
    }
    .padding(10)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  addLog(message: string): void {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog = `[${timestamp}] ${message}\n${this.eventLog}`
  }

  build() {
    Column() {
      Scroll() {
        Column({ space: 20 }) {
          Text('菜单交互模式示例')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Column({ space: 15 }) {
            Text('交互模式统计')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 20 }) {
              Column() {
                Text('菜单显示次数')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.menuShowCount}`)
                  .fontSize(24)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#2196F3')
              }

              Column() {
                Text('最后交互类型')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.lastInteractionType || '无')
                  .fontSize(24)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#4CAF50')
              }

              Column() {
                Text('最后关闭时间')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.lastMenuCloseTime || '无')
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#FF9800')
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)
            .padding(15)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('点击触发菜单')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('点击下方按钮，通过bindMenu方式弹出菜单')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 15 }) {
              Button('点击显示菜单')
                .fontSize(16)
                .width(150)
                .height(50)
                .backgroundColor('#2196F3')
                .bindMenu(this.ClickInteractionMenu)

              Button('点击显示菜单(带触觉反馈)')
                .fontSize(16)
                .width(200)
                .height(50)
                .backgroundColor('#4CAF50')
                .bindMenu(this.ClickInteractionMenu, {
                  hapticFeedbackMode: HapticFeedbackMode.ENABLED
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('长按触发菜单')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('长按下方组件，通过bindContextMenu方式弹出菜单')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 15 }) {
              Column() {
                Text('长按我')
                  .fontSize(20)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#FFFFFF')
              }
              .width(120)
              .height(80)
              .backgroundColor('#FF9800')
              .borderRadius(12)
              .justifyContent(FlexAlign.Center)
              .alignItems(HorizontalAlign.Center)
              .bindContextMenu(this.LongPressInteractionMenu, ResponseType.LongPress)

              Column() {
                Image($r('app.media.app_icon'))
                  .width(60)
                  .height(60)
                  .borderRadius(8)
                Text('图片长按')
                  .fontSize(12)
                  .margin({ top: 5 })
              }
              .width(120)
              .height(100)
              .backgroundColor('#E0E0E0')
              .borderRadius(12)
              .justifyContent(FlexAlign.Center)
              .alignItems(HorizontalAlign.Center)
              .bindContextMenu(this.LongPressInteractionMenu, ResponseType.LongPress, {
                preview: this.PreviewBuilder
              })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('右键触发菜单')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('右键点击下方区域，通过bindContextMenu方式弹出菜单')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Column() {
              Text('右键点击此区域')
                .fontSize(18)
                .fontWeight(FontWeight.Bold)
                .fontColor('#666666')
              Text('展示右键上下文菜单')
                .fontSize(14)
                .fontColor('#999999')
                .margin({ top: 10 })
            }
            .width('100%')
            .height(120)
            .backgroundColor('#F5F5F5')
            .borderRadius(12)
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
            .bindContextMenu(this.RightClickInteractionMenu, ResponseType.RightClick)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('状态变量控制菜单')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('通过@State变量控制菜单的显示和隐藏')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 15 }) {
              Button(this.isShowMenu ? '隐藏菜单' : '显示菜单')
                .fontSize(16)
                .width(140)
                .height(50)
                .backgroundColor(this.isShowMenu ? '#F44336' : '#2196F3')
                .onClick(() => {
                  this.isShowMenu = !this.isShowMenu
                  if (this.isShowMenu) {
                    this.menuShowCount++
                    this.lastInteractionType = '状态控制'
                  }
                })

              Column() {
                if (this.isShowMenu) {
                  this.StateControlledMenu()
                } else {
                  Text('菜单未显示')
                    .fontSize(14)
                    .fontColor('#999999')
                }
              }
              .width(200)
              .height(150)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)
              .justifyContent(FlexAlign.Center)
              .alignItems(HorizontalAlign.Center)
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('混合手势交互')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('同一组件支持多种触发方式')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 20 }) {
              Column() {
                Text('点击触发')
                  .fontSize(14)
                  .fontColor('#666666')
                Button('点击')
                  .fontSize(14)
                  .width(80)
                  .height(40)
                  .margin({ top: 10 })
                  .bindMenu(this.MixedInteractionMenu)
              }
              .padding(15)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)

              Column() {
                Text('长按触发')
                  .fontSize(14)
                  .fontColor('#666666')
                Button('长按')
                  .fontSize(14)
                  .width(80)
                  .height(40)
                  .margin({ top: 10 })
                  .bindContextMenu(this.MixedInteractionMenu, ResponseType.LongPress)
              }
              .padding(15)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)

              Column() {
                Text('右键触发')
                  .fontSize(14)
                  .fontColor('#666666')
                Button('右键')
                  .fontSize(14)
                  .width(80)
                  .height(40)
                  .margin({ top: 10 })
                  .bindContextMenu(this.MixedInteractionMenu, ResponseType.RightClick)
              }
              .padding(15)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('触觉反馈设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('菜单弹出时的触觉反馈效果设置')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 15 }) {
              Button('启用触觉反馈')
                .fontSize(14)
                .width(130)
                .height(45)
                .backgroundColor('#4CAF50')
                .bindMenu(this.HapticFeedbackMenu, {
                  hapticFeedbackMode: HapticFeedbackMode.ENABLED
                })

              Button('禁用触觉反馈')
                .fontSize(14)
                .width(130)
                .height(45)
                .backgroundColor('#9E9E9E')
                .bindMenu(this.HapticFeedbackMenu, {
                  hapticFeedbackMode: HapticFeedbackMode.DISABLED
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('预览图交互')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Text('长按时显示预览图，然后弹出菜单')
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')

            Row({ space: 15 }) {
              Column() {
                Image($r('app.media.app_icon'))
                  .width(80)
                  .height(80)
                  .borderRadius(8)
              }
              .padding(15)
              .backgroundColor('#E0E0E0')
              .borderRadius(12)
              .bindContextMenu(this.PreviewMenu, ResponseType.LongPress, {
                preview: this.PreviewBuilder
              })

              Column() {
                Text('预览模式')
                  .fontSize(14)
                  .fontColor('#666666')
              }
              .padding(15)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)

              Column() {
                Text('图片预览')
                  .fontSize(14)
                  .fontColor('#666666')
              }
              .padding(15)
              .backgroundColor('#F5F5F5')
              .borderRadius(8)
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 10 }) {
            Text('事件日志')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Column() {
              Text(this.eventLog || '暂无事件')
                .fontSize(12)
                .fontColor('#666666')
                .width('100%')
            }
            .width('100%')
            .height(180)
            .padding(10)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Row({ space: 10 }) {
              Button('清空日志')
                .fontSize(14)
                .onClick(() => {
                  this.eventLog = ''
                })

              Button('重置统计')
                .fontSize(14)
                .onClick(() => {
                  this.menuShowCount = 0
                  this.lastInteractionType = ''
                  this.lastMenuCloseTime = ''
                })
            }
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
