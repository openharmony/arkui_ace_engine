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
struct MenuStyleCustomization {
  @State currentFontColor: ResourceColor = Color.Black
  @State currentFontSize: number = 16
  @State currentFontWeight: FontWeight = FontWeight.Normal
  @State currentFontStyle: FontStyle = FontStyle.Normal
  @State currentFontFamily: string = 'HarmonyOS Sans'
  @State currentRadius: Length = 16
  @State currentBgColor: ResourceColor = '#FFFFFF'
  @State currentDividerColor: ResourceColor = '#E0E0E0'
  @State currentDividerWidth: number = 1
  @State currentOutlineWidth: Length = '0vp'
  @State currentOutlineColor: ResourceColor = Color.Transparent
  @State currentBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
  @State menuVisible: boolean = false
  @State eventLog: string = ''

  private iconResource: Resource = $r('app.media.app_icon')

  @Builder
  StyleMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '文件操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '新建文件',
        })
          .onClick(() => {
            this.addLog('点击了：新建文件')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '打开文件',
        })
          .onClick(() => {
            this.addLog('点击了：打开文件')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '保存文件',
        })
          .onClick(() => {
            this.addLog('点击了：保存文件')
          })
      }
      MenuItemGroup({ header: '编辑操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '复制',
          labelInfo: 'Ctrl+C'
        })
          .onClick(() => {
            this.addLog('点击了：复制')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '粘贴',
          labelInfo: 'Ctrl+V'
        })
          .onClick(() => {
            this.addLog('点击了：粘贴')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '剪切',
          labelInfo: 'Ctrl+X'
        })
          .onClick(() => {
            this.addLog('点击了：剪切')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '全选',
          labelInfo: 'Ctrl+A'
        })
          .onClick(() => {
            this.addLog('点击了：全选')
          })
      }
      MenuItemGroup({ header: '视图操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '放大',
        })
          .onClick(() => {
            this.addLog('点击了：放大')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '缩小',
          endIcon: $r('sys.media.ohos_ic_public_minus')
        })
          .onClick(() => {
            this.addLog('点击了：缩小')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '重置视图'
        })
          .onClick(() => {
            this.addLog('点击了：重置视图')
          })
      }
    }
    .font({
      size: this.currentFontSize,
      weight: this.currentFontWeight,
      family: this.currentFontFamily,
      style: this.currentFontStyle
    })
    .fontColor(this.currentFontColor)
    .backgroundColor(this.currentBgColor)
    .outlineColor(this.currentOutlineColor)
    .backgroundBlurStyle(this.currentBlurStyle)
  }

  @Builder
  CompactStyleMenu() {
    Menu() {
      MenuItem({ content: '精简选项1' })
      MenuItem({ content: '精简选项2' })
      MenuItem({ content: '精简选项3' })
    }
    .font({ size: 14, weight: FontWeight.Normal })
    .fontColor('#333333')
    .radius(8)
    .backgroundColor('#F5F5F5')
  }

  @Builder
  RoundedStyleMenu() {
    Menu() {
      MenuItem({ content: '圆角选项A' })
      MenuItem({ content: '圆角选项B' })
      MenuItem({ content: '圆角选项C' })
    }
    .font({ size: 18, weight: FontWeight.Medium })
    .fontColor('#FFFFFF')
    .radius(24)
    .backgroundColor('#2196F3')
  }

  @Builder
  OutlinedStyleMenu() {
    Menu() {
      MenuItem({ content: '描边选项X' })
      MenuItem({ content: '描边选项Y' })
      MenuItem({ content: '描边选项Z' })
    }
    .font({ size: 16, weight: FontWeight.Normal })
    .fontColor('#000000')
    .radius(4)
    .backgroundColor('#FFFFFF')
    .outlineWidth('2vp')
    .outlineColor('#FF5722')
  }

  @Builder
  BlurStyleMenu() {
    Menu() {
      MenuItem({ content: '模糊效果1' })
      MenuItem({ content: '模糊效果2' })
      MenuItem({ content: '模糊效果3' })
    }
    .font({ size: 16, weight: FontWeight.Normal })
    .fontColor('#333333')
    .radius(16)
    .backgroundBlurStyle(BlurStyle.COMPONENT_THICK)
  }

  @Builder
  CustomDividerMenu() {
    Menu() {
      MenuItem({ content: '自定义分割线1' })
      MenuItem({ content: '自定义分割线2' })
      MenuItem({ content: '自定义分割线3' })
      MenuItem({ content: '自定义分割线4' })
    }
    .font({ size: 16, weight: FontWeight.Normal })
    .fontColor('#000000')
    .radius(12)
    .backgroundColor('#FFFFFF')
  }

  addLog(message: string): void {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog = `[${timestamp}] ${message}\n${this.eventLog}`
  }

  build() {
    Column() {
      Scroll() {
        Column({ space: 20 }) {
          Text('菜单样式定制示例')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Column({ space: 15 }) {
            Text('实时样式调整')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Button('显示菜单')
                .fontSize(16)
                .onClick(() => {
                  this.menuVisible = !this.menuVisible
                })
              Text(this.menuVisible ? '菜单已显示' : '菜单已隐藏')
                .fontSize(14)
                .fontColor('#666666')
            }
            .width('100%')
            .justifyContent(FlexAlign.Start)

            if (this.menuVisible) {
              Column() {
                this.StyleMenuBuilder()
              }
              .width('100%')
              .alignItems(HorizontalAlign.Center)
              .padding(10)
              .backgroundColor('#F0F0F0')
              .borderRadius(8)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('字体样式设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('字体大小:')
                .fontSize(14)
                .width(80)
              Slider({
                min: 12,
                max: 28,
                value: this.currentFontSize,
                step: 1
              })
                .width('50%')
                .onChange((value: number) => {
                  this.currentFontSize = value
                })
              Text(`${this.currentFontSize}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('字体粗细:')
                .fontSize(14)
                .width(80)
              Button('正常')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontWeight = FontWeight.Normal
                })
              Button('中等')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontWeight = FontWeight.Medium
                })
              Button('粗体')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontWeight = FontWeight.Bold
                })
              Button('更粗')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontWeight = FontWeight.Bolder
                })
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('字体样式:')
                .fontSize(14)
                .width(80)
              Button('正常')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontStyle = FontStyle.Normal
                })
              Button('斜体')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentFontStyle = FontStyle.Italic
                })
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('字体颜色:')
                .fontSize(14)
                .width(80)
              Button('黑色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#000000')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentFontColor = Color.Black
                })
              Button('白色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#FFFFFF')
                .fontColor('#000000')
                .borderWidth(1)
                .onClick(() => {
                  this.currentFontColor = Color.White
                })
              Button('蓝色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#2196F3')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentFontColor = '#2196F3'
                })
              Button('红色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#F44336')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentFontColor = '#F44336'
                })
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('菜单外观设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('圆角大小:')
                .fontSize(14)
                .width(80)
              Slider({
                min: 0,
                max: 32,
                value: this.currentRadius as number,
                step: 1
              })
                .width('50%')
                .onChange((value: number) => {
                  this.currentRadius = value
                })
              Text(`${this.currentRadius}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('背景颜色:')
                .fontSize(14)
                .width(80)
              Button('白色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#FFFFFF')
                .fontColor('#000000')
                .borderWidth(1)
                .onClick(() => {
                  this.currentBgColor = '#FFFFFF'
                })
              Button('浅灰')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#F5F5F5')
                .fontColor('#000000')
                .onClick(() => {
                  this.currentBgColor = '#F5F5F5'
                })
              Button('蓝色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#2196F3')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentBgColor = '#2196F3'
                })
              Button('透明')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#E0E0E0')
                .fontColor('#000000')
                .onClick(() => {
                  this.currentBgColor = Color.Transparent
                })
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('模糊样式:')
                .fontSize(14)
                .width(80)
              Button('厚')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentBlurStyle = BlurStyle.COMPONENT_THICK
                })
              Button('超厚')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                })
              Button('普通')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentBlurStyle = BlurStyle.COMPONENT_REGULAR
                })
              Button('薄')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentBlurStyle = BlurStyle.COMPONENT_THIN
                })
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('分割线设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('分割线宽度:')
                .fontSize(14)
                .width(80)
              Slider({
                min: 0,
                max: 5,
                value: this.currentDividerWidth,
                step: 1
              })
                .width('50%')
                .onChange((value: number) => {
                  this.currentDividerWidth = value
                })
              Text(`${this.currentDividerWidth}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('分割线颜色:')
                .fontSize(14)
                .width(80)
              Button('灰色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentDividerColor = '#E0E0E0'
                })
              Button('橙色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentDividerColor = '#FF9800'
                })
              Button('蓝色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentDividerColor = '#2196F3'
                })
              Button('透明')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentDividerColor = Color.Transparent
                })
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('外描边设置')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text('描边宽度:')
                .fontSize(14)
                .width(80)
              Button('无')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentOutlineWidth = '0vp'
                })
              Button('1vp')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentOutlineWidth = '1vp'
                })
              Button('2vp')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentOutlineWidth = '2vp'
                })
              Button('3vp')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .onClick(() => {
                  this.currentOutlineWidth = '3vp'
                })
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('描边颜色:')
                .fontSize(14)
                .width(80)
              Button('橙色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#FF5722')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentOutlineColor = '#FF5722'
                })
              Button('绿色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#4CAF50')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentOutlineColor = '#4CAF50'
                })
              Button('紫色')
                .fontSize(12)
                .type(ButtonType.Capsule)
                .height(32)
                .backgroundColor('#9C27B0')
                .fontColor('#FFFFFF')
                .onClick(() => {
                  this.currentOutlineColor = '#9C27B0'
                })
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('预设样式示例')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 15 }) {
              Column() {
                Text('精简样式')
                  .fontSize(14)
                  .margin({ bottom: 8 })
                Button('点击查看')
                  .fontSize(12)
                  .bindMenu(this.CompactStyleMenu)
              }
              .padding(10)
              .backgroundColor('#F9F9F9')
              .borderRadius(8)

              Column() {
                Text('圆角样式')
                  .fontSize(14)
                  .margin({ bottom: 8 })
                Button('点击查看')
                  .fontSize(12)
                  .bindMenu(this.RoundedStyleMenu)
              }
              .padding(10)
              .backgroundColor('#F9F9F9')
              .borderRadius(8)
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)

            Row({ space: 15 }) {
              Column() {
                Text('描边样式')
                  .fontSize(14)
                  .margin({ bottom: 8 })
                Button('点击查看')
                  .fontSize(12)
                  .bindMenu(this.OutlinedStyleMenu)
              }
              .padding(10)
              .backgroundColor('#F9F9F9')
              .borderRadius(8)

              Column() {
                Text('模糊样式')
                  .fontSize(14)
                  .margin({ bottom: 8 })
                Button('点击查看')
                  .fontSize(12)
                  .bindMenu(this.BlurStyleMenu)
              }
              .padding(10)
              .backgroundColor('#F9F9F9')
              .borderRadius(8)
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)

            Row({ space: 15 }) {
              Column() {
                Text('自定义分割线')
                  .fontSize(14)
                  .margin({ bottom: 8 })
                Button('点击查看')
                  .fontSize(12)
                  .bindMenu(this.CustomDividerMenu)
              }
              .padding(10)
              .backgroundColor('#F9F9F9')
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
            .height(150)
            .padding(10)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Button('清空日志')
              .fontSize(14)
              .onClick(() => {
                this.eventLog = ''
              })
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
