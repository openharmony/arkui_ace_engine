/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import uiMaterial from '@ohos.arkui.uiMaterial'

@Entry
@Component
struct ThemeCase {
  @State enableArrow: boolean = true
  @State currentPlacement: Placement = Placement.Bottom
  @State arrowOffset: number = 0
  @State borderRadiusValue: number = 10
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State showInSubWindow: boolean = true
  @State menuWidth: number = 200
  
  @State isDarkMode: boolean = false
  @State themeColor: string = '#FF6B6B'
  @State bgColor: string = '#FFFFFF'
  @State textColor: string = '#000000'
  @State menuBackgroundColor: string = '#F5F5F5'
  
  placementArray: Placement[] = [
    Placement.Top,
    Placement.Bottom,
    Placement.Left,
    Placement.Right,
    Placement.TopLeft,
    Placement.TopRight,
    Placement.BottomLeft,
    Placement.BottomRight
  ]
  @State placementIndex: number = 1
  
  borderRadiusArray: (Length | BorderRadiuses)[] = [
    0,
    10,
    20,
    30,
    50,
    {
      topLeft: 10,
      topRight: 20,
      bottomLeft: 30,
      bottomRight: 40
    }
  ]
  @State borderRadiusIndex: number = 1
  
  blurStyleArray: (BlurStyle | undefined)[] = [
    undefined,
    BlurStyle.Thin,
    BlurStyle.Regular,
    BlurStyle.Thick,
    BlurStyle.BACKGROUND_THIN,
    BlurStyle.BACKGROUND_REGULAR,
    BlurStyle.BACKGROUND_ULTRA_THICK,
    BlurStyle.NONE,
    BlurStyle.COMPONENT_THICK
  ]
  @State blurStyleIndex: number = 0
  
  materialArray: (SystemUiMaterial | undefined)[] = [
    undefined,
    new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }),
    new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
  ]
  @State materialIndex: number = 0
  
  themeColorArray: string[] = [
    '#FF6B6B',
    '#4ECDC4',
    '#45B7D1',
    '#96CEB4',
    '#FFEAA7',
    '#DDA0DD',
    '#98D8C8',
    '#F7DC6F',
    '#BB8FCE',
    '#85C1E9'
  ]
  @State themeColorIndex: number = 0
  
  outlineColorArray: (ResourceColor | undefined)[] = [
    undefined,
    0xff000000,
    0xffffffff,
    0xff00ff00,
    0xff0000ff,
    Color.Red,
    Color.Blue,
    Color.Green,
    Color.Yellow,
    Color.Pink
  ]
  @State outlineColorIndex: number = 0
  
  outlineWidthArray: (Dimension | undefined)[] = [
    undefined,
    1,
    2,
    5,
    10,
    20
  ]
  @State outlineWidthIndex: number = 0
  
  @Builder
  ThemeMenu() {
    Menu() {
      MenuItemGroup({ header: '主题测试菜单' }) {
        MenuItem({ content: '主题测试项1' })
          .onClick(() => {
            console.info('Theme MenuItem 1 clicked')
          })
        MenuItem({ content: '主题测试项2' })
        MenuItem({ content: '主题测试项3' })
        MenuItem({ content: '主题测试项4' })
        MenuItem({ content: '主题测试项5' })
      }
      MenuItem({ content: '单独菜单项' })
        .onClick(() => {
          console.info('Theme standalone MenuItem clicked')
        })
    }
    .width(this.menuWidth)
  }
  
  buildMenuOptions(): MenuOptions {
    return {
      enableArrow: this.enableArrow,
      placement: this.currentPlacement,
      arrowOffset: this.arrowOffset,
      borderRadius: this.borderRadiusArray[this.borderRadiusIndex],
      systemMaterial: this.materialArray[this.materialIndex],
      backgroundBlurStyle: this.blurStyleArray[this.blurStyleIndex],
      showInSubWindow: this.showInSubWindow,
      outlineColor: this.outlineColorArray[this.outlineColorIndex],
      outlineWidth: this.outlineWidthArray[this.outlineWidthIndex],
      onDisappear: () => {
        console.info('Theme Menu disappeared')
      }
    }
  }
  
  toggleTheme() {
    this.isDarkMode = !this.isDarkMode
    if (this.isDarkMode) {
      this.bgColor = '#1A1A1A'
      this.textColor = '#FFFFFF'
      this.menuBackgroundColor = '#333333'
    } else {
      this.bgColor = '#FFFFFF'
      this.textColor = '#000000'
      this.menuBackgroundColor = '#F5F5F5'
    }
  }
  
  build() {
    Column() {
      Scroll() {
        Column({ space: 8 }) {
          Text('深色/浅色模式场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .padding(10)
            .backgroundColor(this.isDarkMode ? '#333333' : '#E0E0E0')
            .fontColor(this.textColor)
            .width('100%')
          
          Row({ space: 10 }) {
            Text('当前模式:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button(this.isDarkMode ? '深色' : '浅色')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.toggleTheme()
              })
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('主题颜色:')
              .fontSize(12)
              .fontColor(this.textColor)
            Row({ space: 5 }) {
              ForEach([0, 1, 2, 3, 4], (index: number) => {
                Button('')
                  .width(20)
                  .height(20)
                  .backgroundColor(this.themeColorArray[index])
                  .borderRadius(10)
                  .onClick(() => {
                    this.themeColorIndex = index
                    this.themeColor = this.themeColorArray[index]
                  })
              })
            }
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('菜单方向:')
              .fontSize(12)
              .fontColor(this.textColor)
            Select([
              { value: 'Top' },
              { value: 'Bottom' },
              { value: 'Left' },
              { value: 'Right' },
              { value: 'TopLeft' },
              { value: 'TopRight' },
              { value: 'BottomLeft' },
              { value: 'BottomRight' }
            ])
              .selected(this.placementIndex)
              .value(this.placementArray[this.placementIndex].toString())
              .onSelect((index: number) => {
                this.placementIndex = index
                this.currentPlacement = this.placementArray[index]
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('启用箭头:')
              .fontSize(12)
              .fontColor(this.textColor)
            Select([{ value: 'false' }, { value: 'true' }])
              .selected(this.enableArrow ? 1 : 0)
              .value(this.enableArrow ? 'true' : 'false')
              .onSelect((index: number) => {
                this.enableArrow = index === 1
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('箭头偏移:')
              .fontSize(12)
              .fontColor(this.textColor)
            Row({ space: 5 }) {
              Button('-10')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset -= 10
                })
              Button('+10')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset += 10
                })
              Button('Reset')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset = 0
                })
            }
            Text('当前: ' + this.arrowOffset)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('边框圆角:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button('切换')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.borderRadiusIndex = (this.borderRadiusIndex + 1) % this.borderRadiusArray.length
              })
            Text('Index: ' + this.borderRadiusIndex)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('模糊样式:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button('切换')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.blurStyleIndex = (this.blurStyleIndex + 1) % this.blurStyleArray.length
              })
            Text('Index: ' + this.blurStyleIndex)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('材质类型:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button('切换')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.materialIndex = (this.materialIndex + 1) % this.materialArray.length
              })
            Text('Index: ' + this.materialIndex)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('边框宽度:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button('切换')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.outlineWidthIndex = (this.outlineWidthIndex + 1) % this.outlineWidthArray.length
              })
            Text('Index: ' + this.outlineWidthIndex)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('边框颜色:')
              .fontSize(12)
              .fontColor(this.textColor)
            Button('切换')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.outlineColorIndex = (this.outlineColorIndex + 1) % this.outlineColorArray.length
              })
            Text('Index: ' + this.outlineColorIndex)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('子窗口:')
              .fontSize(12)
              .fontColor(this.textColor)
            Select([{ value: 'true' }, { value: 'false' }])
              .selected(this.showInSubWindow ? 0 : 1)
              .value(this.showInSubWindow ? 'true' : 'false')
              .onSelect((index: number) => {
                this.showInSubWindow = index === 0
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('菜单宽度:')
              .fontSize(12)
              .fontColor(this.textColor)
            Row({ space: 5 }) {
              Button('-20')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuWidth -= 20
                  if (this.menuWidth < 100) {
                    this.menuWidth = 100
                  }
                })
              Button('+20')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuWidth += 20
                  if (this.menuWidth > 400) {
                    this.menuWidth = 400
                  }
                })
            }
            Text('当前: ' + this.menuWidth)
              .fontSize(12)
              .fontColor(this.textColor)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Divider()
            .margin({ top: 10, bottom: 10 })
            .color(this.textColor)
          
          Text('测试说明:')
            .fontSize(12)
            .fontWeight(FontWeight.Bold)
            .fontColor(this.textColor)
          
          Text('1. 深色模式下菜单背景和颜色自动适配')
            .fontSize(11)
            .fontColor(this.textColor)
            .padding({ left: 10 })
          
          Text('2. 不同主题颜色影响菜单边框和强调色')
            .fontSize(11)
            .fontColor(this.textColor)
            .padding({ left: 10 })
          
          Text('3. 模糊效果在深浅模式下视觉效果不同')
            .fontSize(11)
            .fontColor(this.textColor)
            .padding({ left: 10 })
          
          Text('4. 边框颜色在深色背景下显示效果差异')
            .fontSize(11)
            .fontColor(this.textColor)
            .padding({ left: 10 })
          
          Text('5. Material材质在不同主题下有不同呈现')
            .fontSize(11)
            .fontColor(this.textColor)
            .padding({ left: 10 })
        }
        .width('100%')
      }
      .height(280)
      .width('100%')
      .backgroundColor(this.menuBackgroundColor)
      
      Column() {
        Button('主题测试按钮')
          .width(120)
          .height(60)
          .backgroundColor(this.themeColor)
          .fontColor(Color.White)
          .bindMenu(this.ThemeMenu(), this.buildMenuOptions())
        
        Text('当前主题: ' + (this.isDarkMode ? '深色模式' : '浅色模式'))
          .fontSize(12)
          .fontColor(this.textColor)
          .margin({ top: 20 })
        
        Text('主题颜色: ' + this.themeColor)
          .fontSize(12)
          .fontColor(this.textColor)
          .margin({ top: 10 })
        
        Column() {
          Row() {
            Text('背景: ')
              .fontSize(10)
              .fontColor(this.textColor)
            Text(this.bgColor)
              .fontSize(10)
              .fontColor(this.textColor)
          }
          Row() {
            Text('文本: ')
              .fontSize(10)
              .fontColor(this.textColor)
            Text(this.textColor)
              .fontSize(10)
              .fontColor(this.textColor)
          }
          Row() {
            Text('菜单: ')
              .fontSize(10)
              .fontColor(this.textColor)
            Text(this.menuBackgroundColor)
              .fontSize(10)
              .fontColor(this.textColor)
          }
        }
        .margin({ top: 20 })
        .padding(10)
        .backgroundColor(this.isDarkMode ? '#444444' : '#FFFFFF')
        .borderRadius(8)
        
        Row({ space: 10 }) {
          Button('深色')
            .controlSize(ControlSize.SMALL)
            .onClick(() => {
              if (!this.isDarkMode) {
                this.toggleTheme()
              }
            })
          Button('浅色')
            .controlSize(ControlSize.SMALL)
            .onClick(() => {
              if (this.isDarkMode) {
                this.toggleTheme()
              }
            })
        }
        .margin({ top: 20 })
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor(this.bgColor)
      .justifyContent(FlexAlign.Center)
    }
    .height('100%')
    .width('100%')
    .backgroundColor(this.bgColor)
  }
}