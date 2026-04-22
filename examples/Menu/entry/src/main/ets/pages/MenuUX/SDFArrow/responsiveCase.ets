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
import display from '@ohos.display'

@Entry
@Component
struct ResponsiveCase {
  @State enableArrow: boolean = true
  @State currentPlacement: Placement = Placement.Bottom
  @State arrowOffset: number = 0
  @State borderRadiusValue: number = 10
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State menuWidth: number = 200
  @State menuHeight: number | undefined = undefined
  @State showInSubWindow: boolean = true
  @State screenWidth: number = 360
  @State screenHeight: number = 780
  @State orientation: string = 'portrait'
  @State densityDPI: number = 320
  @State displayScale: number = 1.0
  @State fontScale: number = 1.0
  
  placementArray: Placement[] = [
    Placement.Top,
    Placement.Bottom,
    Placement.Left,
    Placement.Right,
    Placement.TopLeft,
    Placement.TopRight,
    Placement.BottomLeft,
    Placement.BottomRight,
    Placement.LeftTop,
    Placement.LeftBottom,
    Placement.RightTop,
    Placement.RightBottom
  ]
  @State placementIndex: number = 1
  
  densityArray: number[] = [160, 240, 320, 480, 640]
  @State densityIndex: number = 2
  
  scaleArray: number[] = [0.75, 1.0, 1.25, 1.5, 2.0]
  @State scaleIndex: number = 1
  
  fontScaleArray: number[] = [0.85, 1.0, 1.15, 1.3, 1.45]
  @State fontScaleIndex: number = 1
  
  menuWidthPercentArray: number[] = [30, 50, 70, 90, 100]
  @State menuWidthPercentIndex: number = 1
  
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
    BlurStyle.NONE
  ]
  @State blurStyleIndex: number = 0
  
  materialArray: (SystemUiMaterial | undefined)[] = [
    undefined,
    new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }),
    new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
  ]
  @State materialIndex: number = 0
  
  alignRuleArr: AlignRuleOption[] = [
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
  ]
  @State alignRuleIndex: number = 4
  
  @State autoAdapt: boolean = true
  
  @Builder
  ResponsiveMenu() {
    Menu() {
      MenuItemGroup({ header: '响应式菜单' }) {
        MenuItem({ content: '响应式菜单项1' })
          .onClick(() => {
            console.info('Responsive MenuItem 1 clicked')
          })
        MenuItem({ content: '响应式菜单项2' })
        MenuItem({ content: '响应式菜单项3' })
      }
      MenuItemGroup({ header: '第二组' }) {
        MenuItem({ content: '组内项1' })
        MenuItem({ content: '组内项2' })
        MenuItem({ content: '组内项3' })
        MenuItem({ content: '组内项4' })
      }
      MenuItem({ content: '单独菜单项' })
    }
    .width(this.autoAdapt ? `${this.menuWidthPercentArray[this.menuWidthPercentIndex]}%` : this.menuWidth)
    .height(this.menuHeight)
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
      onDisappear: () => {
        console.info('Responsive Menu disappeared')
      }
    }
  }
  
  aboutToAppear() {
    try {
      let displayInfo = display.getDefaultDisplaySync()
      this.screenWidth = displayInfo.width
      this.screenHeight = displayInfo.height
      this.densityDPI = displayInfo.densityDPI
      this.displayScale = displayInfo.densityPixels / displayInfo.densityDPI
      if (displayInfo.width > displayInfo.height) {
        this.orientation = 'landscape'
      } else {
        this.orientation = 'portrait'
      }
    } catch (err) {
      console.error('Failed to get display info: ' + JSON.stringify(err))
    }
  }
  
  build() {
    Column() {
      Scroll() {
        Column({ space: 8 }) {
          Text('响应式布局场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .padding(10)
            .backgroundColor('#E0E0E0')
            .width('100%')
          
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('屏幕信息')
                .fontSize(12)
                .fontWeight(FontWeight.Bold)
              Text('宽度: ' + this.screenWidth + 'px')
                .fontSize(11)
              Text('高度: ' + this.screenHeight + 'px')
                .fontSize(11)
              Text('方向: ' + this.orientation)
                .fontSize(11)
              Text('DPI: ' + this.densityDPI)
                .fontSize(11)
              Text('Scale: ' + this.displayScale.toFixed(2))
                .fontSize(11)
            }
            .layoutWeight(1)
            .padding(10)
            .backgroundColor('#F0F0F0')
            .borderRadius(8)
            
            Column({ space: 5 }) {
              Text('模拟参数')
                .fontSize(12)
                .fontWeight(FontWeight.Bold)
              Row({ space: 5 }) {
                Text('密度:')
                  .fontSize(11)
                Button(this.densityArray[this.densityIndex].toString())
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.densityIndex = (this.densityIndex + 1) % this.densityArray.length
                    this.densityDPI = this.densityArray[this.densityIndex]
                  })
              }
              Row({ space: 5 }) {
                Text('缩放:')
                  .fontSize(11)
                Button(this.scaleArray[this.scaleIndex].toFixed(2))
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.scaleIndex = (this.scaleIndex + 1) % this.scaleArray.length
                    this.displayScale = this.scaleArray[this.scaleIndex]
                  })
              }
              Row({ space: 5 }) {
                Text('字体:')
                  .fontSize(11)
                Button(this.fontScaleArray[this.fontScaleIndex].toFixed(2))
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.fontScaleIndex = (this.fontScaleIndex + 1) % this.fontScaleArray.length
                    this.fontScale = this.fontScaleArray[this.fontScaleIndex]
                  })
              }
            }
            .layoutWeight(1)
            .padding(10)
            .backgroundColor('#F0F0F0')
            .borderRadius(8)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Divider()
            .margin({ top: 5, bottom: 5 })
          
          Row({ space: 10 }) {
            Text('锚点位置:')
              .fontSize(12)
            Select([
              { value: '左上' },
              { value: '上中' },
              { value: '右上' },
              { value: '左中' },
              { value: '居中' },
              { value: '右中' },
              { value: '左下' },
              { value: '下中' },
              { value: '右下' }
            ])
              .selected(this.alignRuleIndex)
              .value(this.getPositionName(this.alignRuleIndex))
              .onSelect((index: number) => {
                this.alignRuleIndex = index
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('菜单方向:')
              .fontSize(12)
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
            Row({ space: 5 }) {
              Button('-20')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset -= 20
                })
              Button('+20')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset += 20
                })
              Button('Reset')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset = 0
                })
            }
            Text('当前: ' + this.arrowOffset)
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('菜单宽度模式:')
              .fontSize(12)
            Select([{ value: '百分比' }, { value: '固定值' }])
              .selected(this.autoAdapt ? 0 : 1)
              .value(this.autoAdapt ? '百分比' : '固定值')
              .onSelect((index: number) => {
                this.autoAdapt = index === 0
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          if (this.autoAdapt) {
            Row({ space: 10 }) {
              Text('宽度百分比:')
                .fontSize(12)
              Button(this.menuWidthPercentArray[this.menuWidthPercentIndex] + '%')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuWidthPercentIndex = (this.menuWidthPercentIndex + 1) % this.menuWidthPercentArray.length
                })
            }
            .width('100%')
            .padding({ left: 10, right: 10 })
          } else {
            Row({ space: 10 }) {
              Text('固定宽度:')
                .fontSize(12)
              Row({ space: 5 }) {
                Button('-50')
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.menuWidth -= 50
                    if (this.menuWidth < 100) {
                      this.menuWidth = 100
                    }
                  })
                Button('+50')
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.menuWidth += 50
                    if (this.menuWidth > 600) {
                      this.menuWidth = 600
                    }
                  })
              }
              Text('当前: ' + this.menuWidth + 'vp')
                .fontSize(12)
            }
            .width('100%')
            .padding({ left: 10, right: 10 })
          }
          
          Row({ space: 10 }) {
            Text('菜单高度:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('undefined')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight = undefined
                })
              Button('200')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight = 200
                })
              Button('400')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight = 400
                })
              Button('600')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight = 600
                })
            }
            Text('当前: ' + (this.menuHeight ?? 'auto'))
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('边框圆角:')
              .fontSize(12)
            Button('切换圆角')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.borderRadiusIndex = (this.borderRadiusIndex + 1) % this.borderRadiusArray.length
              })
            Text('Index: ' + this.borderRadiusIndex)
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('模糊样式:')
              .fontSize(12)
            Button('切换模糊')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.blurStyleIndex = (this.blurStyleIndex + 1) % this.blurStyleArray.length
              })
            Text('Index: ' + this.blurStyleIndex)
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('材质类型:')
              .fontSize(12)
            Button('切换材质')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.materialIndex = (this.materialIndex + 1) % this.materialArray.length
              })
            Text('Index: ' + this.materialIndex)
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('子窗口:')
              .fontSize(12)
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
          
          Divider()
            .margin({ top: 10, bottom: 10 })
          
          Text('测试说明:')
            .fontSize(12)
            .fontWeight(FontWeight.Bold)
          
          Text('1. 百分比宽度模式下菜单会随屏幕尺寸自适应')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('2. 固定宽度模式在不同密度屏幕上显示尺寸不同')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('3. 箭头偏移在不同屏幕尺寸下应有不同效果')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('4. 边框圆角在不同缩放比例下显示大小不同')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('5. 横竖屏切换时菜单位置应自动调整')
            .fontSize(11)
            .padding({ left: 10 })
        }
        .width('100%')
      }
      .height(320)
      .width('100%')
      .backgroundColor('#F5F5F5')
      
      RelativeContainer() {
        Button('响应式菜单')
          .width(100)
          .height(50)
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .bindMenu(this.ResponsiveMenu(), this.buildMenuOptions())
          .backgroundColor('#32CD32')
          .fontColor(Color.White)
        
        Column() {
          Text('屏幕中心参考')
            .fontSize(10)
            .fontColor('#666666')
          Row() {
            Text('W: ' + this.screenWidth)
              .fontSize(10)
              .fontColor('#666666')
            Text(' H: ' + this.screenHeight)
              .fontSize(10)
              .fontColor('#666666')
          }
        }
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#E8E8E8')
    }
    .height('100%')
    .width('100%')
  }
  
  getPositionName(index: number): string {
    const names = ['左上', '上中', '右上', '左中', '居中', '右中', '左下', '下中', '右下']
    return names[index] || '居中'
  }
}