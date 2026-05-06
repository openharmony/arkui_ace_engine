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

@Builder
function BoundaryMenu() {
  Menu() {
    MenuItem({ content: '边界测试菜单项1' })
    MenuItem({ content: '边界测试菜单项2' })
    MenuItem({ content: '边界测试菜单项3' })
    MenuItem({ content: '边界测试菜单项4' })
    MenuItem({ content: '边界测试菜单项5' })
  }
}

@Entry
@Component
struct BoundaryCase {
  @State currentPlacement: Placement = Placement.Bottom
  @State enableArrow: boolean = true
  @State arrowOffset: number = 0
  @State borderRadiusValue: number = 10
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State menuHeight: number = 200
  @State anchorX: number = 0
  @State anchorY: number = 0
  @State showInSubWindow: boolean = true
  @State autoReverse: boolean = true
  @State avoidArea: boolean = true
  
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
  
  @State positionX: number = 0
  @State positionY: number = 0
  
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
  
  @State offsetStep: number = 10
  
  borderRadiusArray: (Length | BorderRadiuses)[] = [
    0,
    5,
    10,
    20,
    30,
    50,
    100,
    {
      topLeft: 10,
      topRight: 20,
      bottomLeft: 30,
      bottomRight: 40
    },
    {
      topLeft: 0,
      topRight: 0,
      bottomLeft: 10,
      bottomRight: 10
    },
    {
      topLeft: 10,
      topRight: 10,
      bottomLeft: 0,
      bottomRight: 0
    }
  ]
  @State borderRadiusIndex: number = 2
  
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
  
  @State menuWidth: number = 200
  
  @Builder
  MyBoundaryMenu() {
    Menu() {
      MenuItem({ content: '边界测试项1' })
        .onClick(() => {
          console.info('Boundary MenuItem 1 clicked')
        })
      MenuItem({ content: '边界测试项2' })
        .onClick(() => {
          console.info('Boundary MenuItem 2 clicked')
        })
      MenuItem({ content: '边界测试项3' })
        .onClick(() => {
          console.info('Boundary MenuItem 3 clicked')
        })
      MenuItemGroup({ header: '分组标题' }) {
        MenuItem({ content: '分组项1' })
        MenuItem({ content: '分组项2' })
      }
      MenuItem({ content: '边界测试项4' })
      MenuItem({ content: '边界测试项5' })
    }
    .width(this.menuWidth)
    .height(this.menuHeight)
  }
  
  buildMenuOptions(): MenuOptions {
    return {
      enableArrow: this.enableArrow,
      placement: this.currentPlacement,
      arrowOffset: this.arrowOffset,
      borderRadius: this.borderRadiusArray[this.borderRadiusIndex],
      anchorPosition: { x: this.anchorX, y: this.anchorY },
      systemMaterial: this.materialArray[this.materialIndex],
      backgroundBlurStyle: this.blurStyleArray[this.blurStyleIndex],
      showInSubWindow: this.showInSubWindow,
      onDisappear: () => {
        console.info('Boundary Menu disappeared')
      }
    }
  }
  
  build() {
    Column() {
      Scroll() {
        Column({ space: 8 }) {
          Text('边界检测场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .padding(10)
            .backgroundColor('#E0E0E0')
            .width('100%')
          
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
              { value: 'BottomRight' },
              { value: 'LeftTop' },
              { value: 'LeftBottom' },
              { value: 'RightTop' },
              { value: 'RightBottom' }
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
              Button('-50')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset -= 50
                })
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
              Button('+50')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffset += 50
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
            Text('锚点偏移:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('X-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.anchorX -= this.offsetStep
                })
              Button('X+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.anchorX += this.offsetStep
                })
              Button('Y-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.anchorY -= this.offsetStep
                })
              Button('Y+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.anchorY += this.offsetStep
                })
            }
            Text('(' + this.anchorX + ',' + this.anchorY + ')')
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('偏移步长:')
              .fontSize(12)
            Select([{ value: '10' }, { value: '20' }, { value: '50' }, { value: '100' }])
              .selected(0)
              .value('10')
              .onSelect((index: number, value: string) => {
                this.offsetStep = parseInt(value)
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('菜单尺寸:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('宽-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuWidth -= 20
                  if (this.menuWidth < 100) {
                    this.menuWidth = 100
                  }
                })
              Button('宽+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuWidth += 20
                  if (this.menuWidth > 500) {
                    this.menuWidth = 500
                  }
                })
              Button('高-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight -= 20
                  if (this.menuHeight < 100) {
                    this.menuHeight = 100
                  }
                })
              Button('高+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight += 20
                  if (this.menuHeight > 600) {
                    this.menuHeight = 600
                  }
                })
            }
            Text('(' + this.menuWidth + 'x' + this.menuHeight + ')')
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
          
          Row({ space: 10 }) {
            Text('组件位置偏移:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('PX-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.positionX -= 20
                })
              Button('PX+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.positionX += 20
                })
              Button('PY-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.positionY -= 20
                })
              Button('PY+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.positionY += 20
                })
              Button('Reset')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.positionX = 0
                  this.positionY = 0
                })
            }
            Text('(' + this.positionX + ',' + this.positionY + ')')
              .fontSize(12)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Divider()
            .margin({ top: 10, bottom: 10 })
          
          Text('测试说明:')
            .fontSize(12)
            .fontWeight(FontWeight.Bold)
          
          Text('1. 将锚点移动到屏幕边界测试菜单是否自动避让')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('2. 不同方向的菜单在边界处应有不同的避让行为')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('3. 箭头偏移过大时箭头应限制在菜单范围内')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('4. 边框圆角在边界处应正确显示')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('5. 子窗口模式下菜单不受主窗口边界限制')
            .fontSize(11)
            .padding({ left: 10 })
        }
        .width('100%')
      }
      .height(280)
      .width('100%')
      .backgroundColor('#F5F5F5')
      
      RelativeContainer() {
        Button('边界测试按钮')
          .width(120)
          .height(60)
          .margin({ left: this.positionX, top: this.positionY })
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .bindMenu(this.MyBoundaryMenu(), this.buildMenuOptions())
          .backgroundColor('#4169E1')
          .fontColor(Color.White)
        
        Text('屏幕边界参考线')
          .fontSize(10)
          .fontColor('#666666')
          .alignRules({
            top: { anchor: '__container__', align: VerticalAlign.Top },
            middle: { anchor: '__container__', align: HorizontalAlign.Center }
          })
          .margin({ top: 5 })
        
        Line()
          .width('100%')
          .height(1)
          .backgroundColor('#CCCCCC')
          .alignRules({
            top: { anchor: '__container__', align: VerticalAlign.Top },
            middle: { anchor: '__container__', align: HorizontalAlign.Center }
          })
          .margin({ top: 20 })
        
        Line()
          .width(1)
          .height('100%')
          .backgroundColor('#CCCCCC')
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center },
            left: { anchor: '__container__', align: HorizontalAlign.Start }
          })
          .margin({ left: 20 })
        
        Line()
          .width(1)
          .height('100%')
          .backgroundColor('#CCCCCC')
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center },
            right: { anchor: '__container__', align: HorizontalAlign.End }
          })
          .margin({ right: 20 })
        
        Line()
          .width('100%')
          .height(1)
          .backgroundColor('#CCCCCC')
          .alignRules({
            bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
            middle: { anchor: '__container__', align: HorizontalAlign.Center }
          })
          .margin({ bottom: 20 })
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