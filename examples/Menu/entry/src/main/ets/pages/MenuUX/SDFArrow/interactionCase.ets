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
struct InteractionCase {
  @State enableArrow: boolean = true
  @State currentPlacement: Placement = Placement.Bottom
  @State arrowOffset: number = 0
  @State borderRadiusValue: number = 10
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State showInSubWindow: boolean = true
  @State menuWidth: number = 200
  @State menuHeight: number | undefined = undefined
  
  @State clickCount: number = 0
  @State longPressCount: number = 0
  @State disappearCount: number = 0
  @State appearCount: number = 0
  @State selectedItems: string[] = []
  @State lastSelectedItem: string = ''
  @State eventLog: string[] = []
  
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
    BlurStyle.NONE
  ]
  @State blurStyleIndex: number = 0
  
  materialArray: (SystemUiMaterial | undefined)[] = [
    undefined,
    new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }),
    new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
  ]
  @State materialIndex: number = 0
  
  responseModeArray: ResponseType[] = [
    ResponseType.LongPress,
    ResponseType.RightClick
  ]
  @State responseModeIndex: number = 0
  
  @State menuType: string = 'bindMenu'
  
  @State menuItemEnabled: boolean = true
  @State menuItemSelected: boolean = false
  
  @Builder
  InteractionMenu() {
    Menu() {
      MenuItemGroup({ header: '交互测试菜单' }) {
        MenuItem({ content: '点击计数项' })
          .enabled(this.menuItemEnabled)
          .selected(this.menuItemSelected)
          .onClick(() => {
            this.clickCount++
            this.logEvent('点击计数项被点击')
            this.selectedItems.push('点击计数项')
            this.lastSelectedItem = '点击计数项'
          })
        MenuItem({ content: '选中切换项' })
          .onClick(() => {
            this.menuItemSelected = !this.menuItemSelected
            this.logEvent('选中切换项被点击, 选中状态: ' + this.menuItemSelected)
            this.lastSelectedItem = '选中切换项'
          })
        MenuItem({ content: '禁用切换项' })
          .onClick(() => {
            this.menuItemEnabled = !this.menuItemEnabled
            this.logEvent('禁用切换项被点击, 启用状态: ' + this.menuItemEnabled)
            this.lastSelectedItem = '禁用切换项'
          })
      }
      MenuItemGroup({ header: '图标菜单项' }) {
        MenuItem({ content: '带开始图标', startIcon: $r('sys.symbol.checkmark') })
          .onClick(() => {
            this.logEvent('带开始图标被点击')
            this.lastSelectedItem = '带开始图标'
          })
        MenuItem({ content: '带结束图标', endIcon: $r('sys.symbol.chevron_right') })
          .onClick(() => {
            this.logEvent('带结束图标被点击')
            this.lastSelectedItem = '带结束图标'
          })
        MenuItem({ content: '双向图标', startIcon: $r('sys.symbol.folder'), endIcon: $r('sys.symbol.chevron_right') })
          .onClick(() => {
            this.logEvent('双向图标被点击')
            this.lastSelectedItem = '双向图标'
          })
      }
      MenuItem({ content: '单独菜单项' })
        .onClick(() => {
          this.logEvent('单独菜单项被点击')
          this.lastSelectedItem = '单独菜单项'
        })
      MenuItem({ content: '长按响应项' })
        .onClick(() => {
          this.longPressCount++
          this.logEvent('长按响应项被点击')
          this.lastSelectedItem = '长按响应项'
        })
    }
    .width(this.menuWidth)
    .height(this.menuHeight)
  }
  
  @Builder
  ContextMenu() {
    Menu() {
      MenuItemGroup({ header: '右键菜单' }) {
        MenuItem({ content: '复制' })
          .onClick(() => {
            this.logEvent('复制被点击')
          })
        MenuItem({ content: '粘贴' })
          .onClick(() => {
            this.logEvent('粘贴被点击')
          })
        MenuItem({ content: '删除' })
          .onClick(() => {
            this.logEvent('删除被点击')
          })
      }
      MenuItem({ content: '属性' })
        .onClick(() => {
          this.logEvent('属性被点击')
        })
    }
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
        this.disappearCount++
        this.logEvent('菜单消失')
      },
      onAppear: () => {
        this.appearCount++
        this.logEvent('菜单出现')
      }
    }
  }
  
  logEvent(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog.unshift(`${timestamp}: ${message}`)
    if (this.eventLog.length > 10) {
      this.eventLog.pop()
    }
  }
  
  clearLogs() {
    this.eventLog = []
    this.clickCount = 0
    this.longPressCount = 0
    this.disappearCount = 0
    this.appearCount = 0
    this.selectedItems = []
    this.lastSelectedItem = ''
  }
  
  build() {
    Column() {
      Scroll() {
        Column({ space: 8 }) {
          Text('交互事件场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .padding(10)
            .backgroundColor('#E0E0E0')
            .width('100%')
          
          Row({ space: 10 }) {
            Text('菜单类型:')
              .fontSize(12)
            Select([
              { value: 'bindMenu' },
              { value: 'bindContextMenu' }
            ])
              .selected(this.menuType === 'bindMenu' ? 0 : 1)
              .value(this.menuType)
              .onSelect((index: number, value: string) => {
                this.menuType = value
              })
              .controlSize(ControlSize.SMALL)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          if (this.menuType === 'bindContextMenu') {
            Row({ space: 10 }) {
              Text('响应模式:')
                .fontSize(12)
              Select([
                { value: 'LongPress' },
                { value: 'RightClick' }
              ])
                .selected(this.responseModeIndex)
                .value(this.responseModeArray[this.responseModeIndex].toString())
                .onSelect((index: number) => {
                  this.responseModeIndex = index
                })
                .controlSize(ControlSize.SMALL)
            }
            .width('100%')
            .padding({ left: 10, right: 10 })
          }
          
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
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('边框圆角:')
              .fontSize(12)
            Button('切换')
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
            Button('切换')
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
            Button('切换')
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
            .margin({ top: 5, bottom: 5 })
          
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
                })
              Button('高-')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.menuHeight === undefined) {
                    this.menuHeight = 300
                  } else {
                    this.menuHeight -= 50
                    if (this.menuHeight < 100) {
                      this.menuHeight = 100
                    }
                  }
                })
              Button('高+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.menuHeight === undefined) {
                    this.menuHeight = 300
                  } else {
                    this.menuHeight += 50
                  }
                })
              Button('Auto')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuHeight = undefined
                })
            }
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Divider()
            .margin({ top: 5, bottom: 5 })
          
          Row({ space: 10 }) {
            Text('统计信息')
              .fontSize(12)
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('点击次数: ' + this.clickCount)
              .fontSize(11)
            Text('长按次数: ' + this.longPressCount)
              .fontSize(11)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('出现次数: ' + this.appearCount)
              .fontSize(11)
            Text('消失次数: ' + this.disappearCount)
              .fontSize(11)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('最后选中: ' + this.lastSelectedItem)
              .fontSize(11)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Button('清除日志')
              .controlSize(ControlSize.SMALL)
              .onClick(() => {
                this.clearLogs()
              })
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
        }
        .width('100%')
      }
      .height(260)
      .width('100%')
      .backgroundColor('#F5F5F5')
      
      Column() {
        if (this.menuType === 'bindMenu') {
          Button('交互测试按钮')
            .width(120)
            .height(60)
            .backgroundColor('#FF6347')
            .fontColor(Color.White)
            .bindMenu(this.InteractionMenu(), this.buildMenuOptions())
        } else if (this.menuType === 'bindContextMenu') {
          Button('右键/长按菜单')
            .width(120)
            .height(60)
            .backgroundColor('#9370DB')
            .fontColor(Color.White)
            .bindContextMenu(this.ContextMenu(), this.responseModeArray[this.responseModeIndex], this.buildMenuOptions())
        }
        
        Divider()
          .margin({ top: 20, bottom: 10 })
        
        Text('事件日志')
          .fontSize(12)
          .fontWeight(FontWeight.Bold)
        
        List({ space: 5 }) {
          ForEach(this.eventLog, (log: string, index: number) => {
            ListItem() {
              Text(log)
                .fontSize(10)
                .fontColor('#666666')
                .width('100%')
            }
          }, (log: string, index: number) => index.toString())
        }
        .width('90%')
        .height(150)
        .backgroundColor('#F0F0F0')
        .borderRadius(8)
        .padding(5)
        
        Text('测试说明:')
          .fontSize(12)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 10 })
        
        Text('1. 点击菜单项触发onClick事件并记录')
          .fontSize(11)
          .padding({ left: 10 })
        
        Text('2. 长按/右键触发bindContextMenu菜单')
          .fontSize(11)
          .padding({ left: 10 })
        
        Text('3. MenuItem的enabled/selected状态可切换')
          .fontSize(11)
          .padding({ left: 10 })
        
        Text('4. startIcon/endIcon图标显示测试')
          .fontSize(11)
          .padding({ left: 10 })
        
        Text('5. onAppear/onDisappear生命周期回调')
          .fontSize(11)
          .padding({ left: 10 })
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#E8E8E8')
      .justifyContent(FlexAlign.Start)
      .padding(20)
    }
    .height('100%')
    .width('100%')
  }
}