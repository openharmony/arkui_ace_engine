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
import { ComponentContent } from '@kit.ArkUI'

@Builder
function MenuA() {
  Menu() {
    MenuItemGroup({ header: '菜单A' }) {
      MenuItem({ content: '菜单A-项目1' })
      MenuItem({ content: '菜单A-项目2' })
      MenuItem({ content: '菜单A-项目3' })
    }
  }
}

@Builder
function MenuB() {
  Menu() {
    MenuItemGroup({ header: '菜单B' }) {
      MenuItem({ content: '菜单B-项目1' })
      MenuItem({ content: '菜单B-项目2' })
      MenuItem({ content: '菜单B-项目3' })
    }
  }
}

@Builder
function MenuC() {
  Menu() {
    MenuItemGroup({ header: '菜单C' }) {
      MenuItem({ content: '菜单C-项目1' })
      MenuItem({ content: '菜单C-项目2' })
      MenuItem({ content: '菜单C-项目3' })
    }
  }
}

@Builder
function MenuD() {
  Menu() {
    MenuItemGroup({ header: '菜单D' }) {
      MenuItem({ content: '菜单D-项目1' })
      MenuItem({ content: '菜单D-项目2' })
      MenuItem({ content: '菜单D-项目3' })
    }
  }
}

@Builder
function NestedMenu() {
  Menu() {
    MenuItem({ content: '父菜单项1' })
    MenuItem({ content: '父菜单项2' })
    MenuItem({ content: '父菜单项3' })
    MenuItemGroup({ header: '子菜单组' }) {
      MenuItem({ content: '子菜单项1' })
      MenuItem({ content: '子菜单项2' })
      MenuItem({ content: '子菜单项3' })
    }
    MenuItem({ content: '父菜单项4' })
  }
}

const largeMenuItems: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]

@Builder
function LargeMenu() {
  Menu() {
    ForEach(largeMenuItems, (item: number) => {
      MenuItem({ content: '大量菜单项-' + (item + 1) })
    }, (item: number): string => item.toString())
  }
}

@Entry
@Component
struct MultiMenuCase {
  @State enableArrow: boolean = true
  @State placementA: Placement = Placement.Bottom
  @State placementB: Placement = Placement.Top
  @State placementC: Placement = Placement.Left
  @State placementD: Placement = Placement.Right
  @State arrowOffsetA: number = 0
  @State arrowOffsetB: number = 0
  @State arrowOffsetC: number = 0
  @State arrowOffsetD: number = 0
  @State showInSubWindowA: boolean = true
  @State showInSubWindowB: boolean = true
  @State showInSubWindowC: boolean = true
  @State showInSubWindowD: boolean = true
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  
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
  
  @State placementIndexA: number = 1
  @State placementIndexB: number = 0
  @State placementIndexC: number = 2
  @State placementIndexD: number = 3
  
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
  
  @State menuWidthA: number = 150
  @State menuWidthB: number = 150
  @State menuWidthC: number = 150
  @State menuWidthD: number = 150
  
  @State showMenuA: boolean = false
  @State showMenuB: boolean = false
  @State showMenuC: boolean = false
  @State showMenuD: boolean = false
  
  @State activeMenuCount: number = 0
  
  @Builder
  MenuAContent() {
    Menu() {
      MenuItemGroup({ header: '菜单A' }) {
        MenuItem({ content: '菜单A-项目1' })
          .onClick(() => {
            console.info('MenuA Item1 clicked')
          })
        MenuItem({ content: '菜单A-项目2' })
        MenuItem({ content: '菜单A-项目3' })
      }
    }
    .width(this.menuWidthA)
  }
  
  @Builder
  MenuBContent() {
    Menu() {
      MenuItemGroup({ header: '菜单B' }) {
        MenuItem({ content: '菜单B-项目1' })
        MenuItem({ content: '菜单B-项目2' })
        MenuItem({ content: '菜单B-项目3' })
      }
    }
    .width(this.menuWidthB)
  }
  
  @Builder
  MenuCContent() {
    Menu() {
      MenuItemGroup({ header: '菜单C' }) {
        MenuItem({ content: '菜单C-项目1' })
        MenuItem({ content: '菜单C-项目2' })
        MenuItem({ content: '菜单C-项目3' })
      }
    }
    .width(this.menuWidthC)
  }
  
  @Builder
  MenuDContent() {
    Menu() {
      MenuItemGroup({ header: '菜单D' }) {
        MenuItem({ content: '菜单D-项目1' })
        MenuItem({ content: '菜单D-项目2' })
        MenuItem({ content: '菜单D-项目3' })
      }
    }
    .width(this.menuWidthD)
  }
  
  buildMenuOptions(placement: Placement, arrowOffset: number, showInSubWindow: boolean): MenuOptions {
    return {
      enableArrow: this.enableArrow,
      placement: placement,
      arrowOffset: arrowOffset,
      borderRadius: this.borderRadiusArray[this.borderRadiusIndex],
      systemMaterial: this.materialArray[this.materialIndex],
      backgroundBlurStyle: this.blurStyleArray[this.blurStyleIndex],
      showInSubWindow: showInSubWindow,
      onDisappear: () => {
        this.activeMenuCount = Math.max(0, this.activeMenuCount - 1)
      }
    }
  }
  
  build() {
    Column() {
      Scroll() {
        Column({ space: 8 }) {
          Text('多菜单场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .padding(10)
            .backgroundColor('#E0E0E0')
            .width('100%')
          
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
          
          Divider()
            .margin({ top: 5, bottom: 5 })
          
          Text('各菜单独立配置')
            .fontSize(12)
            .fontWeight(FontWeight.Bold)
            .padding({ left: 10 })
          
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('菜单A方向')
                .fontSize(11)
              Select([
                { value: 'Top' },
                { value: 'Bottom' },
                { value: 'Left' },
                { value: 'Right' }
              ])
                .selected(this.placementIndexA)
                .value(this.placementArray[this.placementIndexA].toString())
                .onSelect((index: number) => {
                  this.placementIndexA = index
                  this.placementA = this.placementArray[index]
                })
                .controlSize(ControlSize.SMALL)
            }
            .layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('菜单B方向')
                .fontSize(11)
              Select([
                { value: 'Top' },
                { value: 'Bottom' },
                { value: 'Left' },
                { value: 'Right' }
              ])
                .selected(this.placementIndexB)
                .value(this.placementArray[this.placementIndexB].toString())
                .onSelect((index: number) => {
                  this.placementIndexB = index
                  this.placementB = this.placementArray[index]
                })
                .controlSize(ControlSize.SMALL)
            }
            .layoutWeight(1)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('菜单C方向')
                .fontSize(11)
              Select([
                { value: 'Top' },
                { value: 'Bottom' },
                { value: 'Left' },
                { value: 'Right' }
              ])
                .selected(this.placementIndexC)
                .value(this.placementArray[this.placementIndexC].toString())
                .onSelect((index: number) => {
                  this.placementIndexC = index
                  this.placementC = this.placementArray[index]
                })
                .controlSize(ControlSize.SMALL)
            }
            .layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('菜单D方向')
                .fontSize(11)
              Select([
                { value: 'Top' },
                { value: 'Bottom' },
                { value: 'Left' },
                { value: 'Right' }
              ])
                .selected(this.placementIndexD)
                .value(this.placementArray[this.placementIndexD].toString())
                .onSelect((index: number) => {
                  this.placementIndexD = index
                  this.placementD = this.placementArray[index]
                })
                .controlSize(ControlSize.SMALL)
            }
            .layoutWeight(1)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('箭头偏移:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('A+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffsetA += 10
                })
              Button('B+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffsetB += 10
                })
              Button('C+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffsetC += 10
                })
              Button('D+')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.arrowOffsetD += 10
                })
            }
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('当前偏移:')
              .fontSize(12)
            Text('A:' + this.arrowOffsetA)
              .fontSize(11)
            Text('B:' + this.arrowOffsetB)
              .fontSize(11)
            Text('C:' + this.arrowOffsetC)
              .fontSize(11)
            Text('D:' + this.arrowOffsetD)
              .fontSize(11)
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Row({ space: 10 }) {
            Text('子窗口:')
              .fontSize(12)
            Row({ space: 5 }) {
              Button('A:' + (this.showInSubWindowA ? 'Y' : 'N'))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.showInSubWindowA = !this.showInSubWindowA
                })
              Button('B:' + (this.showInSubWindowB ? 'Y' : 'N'))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.showInSubWindowB = !this.showInSubWindowB
                })
              Button('C:' + (this.showInSubWindowC ? 'Y' : 'N'))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.showInSubWindowC = !this.showInSubWindowC
                })
              Button('D:' + (this.showInSubWindowD ? 'Y' : 'N'))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.showInSubWindowD = !this.showInSubWindowD
                })
            }
          }
          .width('100%')
          .padding({ left: 10, right: 10 })
          
          Divider()
            .margin({ top: 5, bottom: 5 })
          
          Text('测试说明:')
            .fontSize(12)
            .fontWeight(FontWeight.Bold)
          
          Text('1. 点击各按钮同时显示多个菜单')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('2. 不同菜单可配置不同的方向和箭头偏移')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('3. 子窗口模式下多个菜单独立显示')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('4. 嵌套菜单测试多级菜单显示')
            .fontSize(11)
            .padding({ left: 10 })
          
          Text('5. 大量菜单项测试滚动和性能')
            .fontSize(11)
            .padding({ left: 10 })
        }
        .width('100%')
      }
      .height(300)
      .width('100%')
      .backgroundColor('#F5F5F5')
      
      Column() {
        Row() {
          Button('菜单A')
            .width(80)
            .height(40)
            .backgroundColor('#FF6B6B')
            .fontColor(Color.White)
            .bindMenu(this.MenuAContent(), this.buildMenuOptions(this.placementA, this.arrowOffsetA, this.showInSubWindowA))
            .onClick(() => {
              this.activeMenuCount++
            })
          
          Blank().width(20)
          
          Button('菜单B')
            .width(80)
            .height(40)
            .backgroundColor('#4ECDC4')
            .fontColor(Color.White)
            .bindMenu(this.MenuBContent(), this.buildMenuOptions(this.placementB, this.arrowOffsetB, this.showInSubWindowB))
            .onClick(() => {
              this.activeMenuCount++
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .margin({ top: 50 })
        
        Row() {
          Button('菜单C')
            .width(80)
            .height(40)
            .backgroundColor('#45B7D1')
            .fontColor(Color.White)
            .bindMenu(this.MenuCContent(), this.buildMenuOptions(this.placementC, this.arrowOffsetC, this.showInSubWindowC))
            .onClick(() => {
              this.activeMenuCount++
            })
          
          Blank().width(20)
          
          Button('菜单D')
            .width(80)
            .height(40)
            .backgroundColor('#96CEB4')
            .fontColor(Color.White)
            .bindMenu(this.MenuDContent(), this.buildMenuOptions(this.placementD, this.arrowOffsetD, this.showInSubWindowD))
            .onClick(() => {
              this.activeMenuCount++
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .margin({ top: 20 })
        
        Row() {
          Button('嵌套菜单')
            .width(120)
            .height(40)
            .backgroundColor('#FFEAA7')
            .fontColor(Color.Black)
            .bindMenu(NestedMenu, {
              enableArrow: this.enableArrow,
              placement: Placement.Bottom,
              borderRadius: this.borderRadiusArray[this.borderRadiusIndex],
              systemMaterial: this.materialArray[this.materialIndex],
              backgroundBlurStyle: this.blurStyleArray[this.blurStyleIndex],
              showInSubWindow: true,
              onDisappear: () => {
                console.info('Nested Menu disappeared')
              }
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .margin({ top: 20 })
        
        Row() {
          Button('大量菜单项')
            .width(120)
            .height(40)
            .backgroundColor('#DDA0DD')
            .fontColor(Color.Black)
            .bindMenu(LargeMenu, {
              enableArrow: this.enableArrow,
              placement: Placement.Bottom,
              borderRadius: this.borderRadiusArray[this.borderRadiusIndex],
              systemMaterial: this.materialArray[this.materialIndex],
              backgroundBlurStyle: this.blurStyleArray[this.blurStyleIndex],
              showInSubWindow: true,
              onDisappear: () => {
                console.info('Large Menu disappeared')
              }
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .margin({ top: 20 })
        
        Text('活跃菜单数: ' + this.activeMenuCount)
          .fontSize(12)
          .fontColor('#666666')
          .margin({ top: 20 })
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#E8E8E8')
    }
    .height('100%')
    .width('100%')
  }
}