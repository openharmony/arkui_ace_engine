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

/*
* 验证Menu的divider分割线样式: Menu和菜单控制
 */
import { LengthUnit } from '@ohos.arkui.node';
import { MyComponent } from '../../common/MyComponent'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_13 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State menuShow: boolean[] = [false, false, false]

  @State subMenuMode: SubMenuExpandingMode = 0

  //divider测试参数
  @State menuDividerTestList: (DividerStyleOptions | undefined)[] = [
  //1
    ,
    //2
    undefined,
    //3
    {},
    //4
    {
      strokeWidth: undefined,
      color: undefined,
      startMargin: undefined,
      endMargin: undefined
    },
    //5
    {
      strokeWidth: {value: -10, unit: LengthUnit.VP}, //NA
      color: undefined,
      startMargin: undefined,
      endMargin: undefined
    },
    //6
    {
      strokeWidth: {value: -1.5, unit: LengthUnit.VP},  //NA
      color: undefined,
      startMargin: undefined,
      endMargin: undefined
    },
    //7
    {
      strokeWidth: {value: 0, unit: LengthUnit.VP},  //NA
      color: undefined,
      startMargin: undefined,
      endMargin: undefined
    },
    //8
    {
      strokeWidth: {value: 1, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: -10, unit: LengthUnit.VP},
      endMargin: {value: -10, unit: LengthUnit.VP}
    },
    //9
    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: -1.5, unit: LengthUnit.VP},
      endMargin: {value: -1.5, unit: LengthUnit.VP}
    },
    //10
    {
      strokeWidth: {value: 10, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 0, unit: LengthUnit.VP},
      endMargin: {value: 0, unit: LengthUnit.VP}
    },
    //11
    {
      strokeWidth: {value: 60, unit: LengthUnit.VP},
      color: '#392F49',
      startMargin: {value: 1, unit: LengthUnit.VP},
      endMargin: {value: 1, unit: LengthUnit.VP}
    },
    //12
    {
      strokeWidth: {value: 3.0, unit: LengthUnit.PX},
      color: 'rgba(57, 47, 73, 0.2)',
      startMargin: {value: 1.5, unit: 2},
      endMargin: {value: 1.5, unit: 2}
    },
    //13
    {
      strokeWidth: {value: 3.0, unit: 0},
      color: 0XFF3C4B34,
      startMargin: {value: 10, unit: 0},
      endMargin: {value: 10, unit: 0}
    },
    //14
    {
      strokeWidth: {value: 3.0, unit: 2},
      color: $r('app.color.Color_red'),
      startMargin: {value: 60, unit: LengthUnit.VP},
      endMargin: {value: 60, unit: LengthUnit.VP}
    },
    //15
    {
      strokeWidth: {value: 0.2, unit: 3},  //百分比类型
      color: $r('app.string.EntryAbility_label'),
      startMargin: {value: 120, unit: 4},
      endMargin: {value: 120, unit: 4},
    },
    //16
    {
      strokeWidth: {value: 3.0, unit: 4},
      color: $r('app.color.Color_green'),
      startMargin: {value: 0.3, unit: 3},  //百分比类型
      endMargin: {value: 0.3, unit: 3}  //百分比类型
    },

    //17
    {
      strokeWidth: {value: 3.0, unit: 7},  //unit枚举类型异常值  NA
      color: '#392F49',
      startMargin: {value: 1, unit: LengthUnit.VP},
      endMargin: {value: 1, unit: LengthUnit.VP}
    },
    //18
    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: 'Color.Pink',  //颜色字符串异常值
      startMargin: {value: -1.5, unit: LengthUnit.VP},
      endMargin: {value: -1.5, unit: LengthUnit.VP}
    },
    //19
    {
      strokeWidth: {value: 10, unit: LengthUnit.VP},
      color: 'Pink',  //颜色字符串异常值
      startMargin: {value: 0, unit: LengthUnit.VP},
      endMargin: {value: 0, unit: LengthUnit.VP}
    },
  ]

  @State select: boolean = true
  private iconStr: ResourceStr = $r('app.media.app_icon')
  private iconStr2: ResourceStr = $r('app.media.app_icon')  //设置子菜单的icon

  //Menu不设置分割线
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ 
        content: '复制',
        labelInfo: 'Ctrl+C' 
      })
      MenuItem({ 
        content: '粘贴', 
        labelInfo: 'Ctrl+V' 
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '选项1',
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '选项2',
          endIcon: this.iconStr2,
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: '选项',
        endIcon: this.iconStr2,
      })
    }
  }
  @Builder
  MenuBuilder(){
    Menu() {
      MenuItem({ 
        startIcon: $r('app.media.app_icon'), 
        content: '菜单选项1'
      })
        .borderWidth(1.0)
        .selectIcon(true)
        .selected(this.select)
        .onChange( () => {
          this.select = !this.select
        })
      MenuItem({ 
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项2'
      })
        .enabled(false)
        .borderRadius(24)
      MenuItem({
        startIcon: this.iconStr,
        content: '次级菜单',
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu()
      })

      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '次级菜单-1',
          endIcon: this.iconStr2,
          builder: () => this.SubMenu()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项3',
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项4',
      })
    }
    .subMenuExpandingMode(this.subMenuMode)
    .backgroundColor('#B6C5D1')
  }

  //Menu设置分隔线
  @Builder
  SubMenu_Divider() {
    Menu() {
      MenuItem({
        content: '复制',
        labelInfo: 'Ctrl+C'
      })
      MenuItem({ 
        content: '粘贴',
        labelInfo: 'Ctrl+V'
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '选项1',
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '选项2',
          endIcon: this.iconStr2,
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: '选项',
        endIcon: this.iconStr2,
      })
    }
    .menuItemDivider(this.menuDividerTestList[this.index[0]])
    .menuItemGroupDivider(this.menuDividerTestList[this.index[0]])
  }
  @Builder
  MenuBuilder_Divider(){
    Menu() {
      MenuItem({ 
        startIcon: $r('app.media.app_icon'), 
        content: '菜单选项1' 
      })
        .borderWidth(1.0)
        .selectIcon(true)
        .selected(this.select)
        .onChange( () => {
          this.select = !this.select
        })
      MenuItem({ 
        startIcon: $r('app.media.app_icon'), 
        content: '菜单选项2' 
      })
        .enabled(false)
        .borderRadius(24)
      MenuItem({
        startIcon: this.iconStr,
        content: '次级菜单',
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu_Divider()
      })

      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '次级菜单-1',
          endIcon: this.iconStr2,
          builder: () => this.SubMenu_Divider()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项3',
        })
      }

      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项4',
      })
    }
    .subMenuExpandingMode(this.subMenuMode)
    .backgroundColor('#D2CAB3')
    .menuItemDivider(this.menuDividerTestList[this.index[0]])
    .menuItemGroupDivider(this.menuDividerTestList[this.index[0]])
  }

  //
  @State dividerLayoutInfo: string = 'item-group-item布局'
  @Builder
  MenuItemGroupBuilder() {
    MenuItemGroup({ header: '小标题' }) {
      MenuItem({
        startIcon: this.iconStr,
        content: 'group选项-0',
        endIcon: this.iconStr2,
        builder: () => this.SubMenu_Divider()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: 'group选项-1',
      })
    }
  }

  @Builder
  MenuItemGroupBuilder_inRow(){
    Row(){
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: 'group选项-0',
          endIcon: this.iconStr2,
          builder: () => this.SubMenu_Divider()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: 'group选项-1',
        })
      }
    }
  }

  @Builder
  MenuBuilder_layout_divider() {
    Menu(){
      if (this.dividerLayoutInfo === 'item-group-item布局') {
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-0' 
        })
          .enabled(false)
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-1' 
        })
      } else if (this.dividerLayoutInfo === 'item布局') {
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-1' 
        })
      } else if (this.dividerLayoutInfo === 'group布局') {
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
      } else if (this.dividerLayoutInfo === 'group特殊布局') {
        this.MenuItemGroupBuilder_inRow()
      }

      else if (this.dividerLayoutInfo === 'item-item布局') {
        MenuItem({ 
            startIcon: $r('app.media.app_icon'),
            content: 'item选项-0' 
        })
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-1'
        })
      }
      else if (this.dividerLayoutInfo === 'group-group布局') {
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
      }
      else if (this.dividerLayoutInfo === 'item-group布局') {
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-0'
        })
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
      }
      else if (this.dividerLayoutInfo === 'group-item布局') {
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: 'group选项-0',
            endIcon: this.iconStr2,
            builder: () => this.SubMenu_Divider()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: 'group选项-1',
          })
        }
        MenuItem({ 
            startIcon: $r('app.media.app_icon'),
            content: 'item选项-0'
        })
      }

      else if (this.dividerLayoutInfo === 'item-group特殊布局') {
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-0' 
        })
        this.MenuItemGroupBuilder_inRow()
      }
      else if (this.dividerLayoutInfo === 'group-item特殊布局') {
        this.MenuItemGroupBuilder_inRow()
        MenuItem({ 
            startIcon: $r('app.media.app_icon'), 
            content: 'item选项-0' 
        })
      }
    }
  }

  build() {
    Scroll(this.scroller){
      Column({space : 5}) {
        Text('验证Menu的divider分割线')
          .paramTextStyle()
        Column({space: 5}){
          Text(`子菜单类型: ${this.subMenuMode}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'SIDE', func: () => {
              this.subMenuMode = 0
            }})
            MyComponent({title: 'EMBEDDED', func: () => {
              this.subMenuMode = 1
            }})
            MyComponent({title: 'STACK', func: () => {
              this.subMenuMode = 2
            }})
          }
        }
        .columnStyle()
        Column({space : 5}){
          Text(`Menu不设置menuItemDivider和menuItemGroupDivider`)
            .paramTextStyle()
          //Menu设置为父容器验证不设置分割线的分割线绘制
          Text(`bindMenu: unset_divider`)
            .backgroundColor(Color.Orange)
            .bindMenu(this.MenuBuilder())
        }
        .columnStyle()

        Column({space : 5}){
          Text(`Menu设置menuItemDivider和menuItemGroupDivider`)
            .paramTextStyle()
          Row({space:2}){
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuDividerTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({ title: 'Test0+', func: () => {
              this.index[0]++
              if (this.index[0] == this.menuDividerTestList.length) {
                this.index[0] = 0
              }
            } })
            MyComponent({ title: 'Test0-', func: () => {
              this.index[0]--
              if (this.index[0] <= -1) {
                this.index[0] = this.menuDividerTestList.length - 1
              }
            } })
          }
          Text(`bindContextMenu: set_divider`)
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.menuShow[1], this.MenuBuilder_Divider(), {
              preview: MenuPreviewMode.IMAGE,
              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
            .onClick( () => {
              this.menuShow[1] = true
            })
        }
        .columnStyle()

        Column({space: 5}){
          Text(`子组件Item/ItemGroup不同布局对分隔线的影响`)
            .paramTextStyle()

          Select([
            { value: 'item-group-item布局' },
            { value: 'item布局' },
            { value: 'group布局' },
            { value: 'group特殊布局' },

            { value: 'item-item布局' },
            { value: 'group-group布局' },
            { value: 'item-group布局' },
            { value: 'group-item布局' },

            { value: 'group-item特殊布局' },
            { value: 'item-group特殊布局' },
          ])
            .value('item-group-item布局')
            .selected(0)
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case value:
                  this.dividerLayoutInfo = value
                  break;
              }
            })
            .key('select_dividerLayout')

          Text(`菜单选项不同布局的分割线绘制`)
            .backgroundColor(Color.Orange)
            .bindMenu(this.MenuBuilder_layout_divider())
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}