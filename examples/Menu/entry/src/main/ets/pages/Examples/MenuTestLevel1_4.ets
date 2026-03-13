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
* 验证Menu的divider分割线样式: 空Item, 一个Item和ItemGroup, ForEach的超多Item, 设置Menu有padding, 设置if语句
 */
import { LengthUnit } from '@ohos.arkui.node';
import { LengthMetrics } from '@kit.ArkUI';

@Component
export struct MenuItemGroup_Comp {
  build() {
    this.MenuItemGroupBuilder()
  }

  @Builder
  MenuItemGroupBuilder() {
    MenuItemGroup({header: '标题'}) {
      MenuItem({ content: '菜单选项' })
    }
  }
}

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuTestLevel1_4 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State menuShow: boolean[] = [false, false, false]

  private iconStr: ResourceStr = $r('app.media.app_icon')
  private iconStr2: ResourceStr = $r('app.media.app_icon')

  //空Item和ItemGroup
  @Builder
  BlankMenu() {
    Menu(){
    }
    .backgroundColor('#C2B1C8')
    .width(240)
    .height(60)
    .menuItemDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value:2, unit: LengthUnit.VP}
    },)
    .menuItemGroupDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value: 2, unit: LengthUnit.VP}
    },)
  }
  //一个Item和ItemGroup
  @Builder
  OneItemMenu() {
    Menu(){
      MenuItemGroup({ header: '头标', footer: '尾标' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '菜单选项1',
          endIcon: this.iconStr2,
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项2',
          endIcon: this.iconStr2,
        })
      }
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
    }
    .backgroundColor('#A6C2BE')
    .menuItemDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value:2, unit: LengthUnit.VP}
    },)
    .menuItemGroupDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value: 2, unit: LengthUnit.VP}
    },)
  }
  //超多Item和ItemGroup
  @State itemIndex: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11 ,12, 13, 14, 15, 16, 17, 18, 19, 20]
  @Builder
  MuchItemsMenu(){
    Menu(){
      ForEach(this.itemIndex, (item: number) => {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: `菜单选项` + item.toString()})
      })
      ForEach(this.itemIndex, (item: number) => {
        MenuItemGroup({ header: '头标' + item.toString(), footer: '尾标' + item.toString() }) {
          MenuItem({
            startIcon: this.iconStr,
            content: '菜单选项1',
            endIcon: this.iconStr2,
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: '菜单选项2',
            endIcon: this.iconStr2,
          })
        }
      })
    }
    .backgroundColor('#B6C6B3')
    .menuItemDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value:2, unit: LengthUnit.VP}
    },)
    .menuItemGroupDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value: 2, unit: LengthUnit.VP}
    },)
  }
  //Menu设置padding:Item和ItemGroup
  @Builder
  ItemMenu_Padding() {
    Menu(){
      MenuItemGroup({ header: '头标', footer: '尾标' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '菜单选项1',
          endIcon: this.iconStr2,
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项2',
          endIcon: this.iconStr2,
        })
      }
      .margin({top: 5, bottom: 5})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .margin({top: 5, bottom: 5})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .margin({top: 5, bottom: 5})
    }
    .backgroundColor('#B6C5D1')
    .borderWidth(1.0)
    .padding(20)
    .menuItemDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value:2, unit: LengthUnit.VP}
    },)
    .menuItemGroupDivider(    {
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value: 2, unit: LengthUnit.VP}
    },)
  }

  //Menu设置If绘制MenuItem
  @State menuItemState: boolean = false
  @State menuItemGroupState: boolean = false
  @Builder
  ItemMenu_If() {
    Menu(){
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '绘制MenuItem' })
        .selected(this.menuItemState)
        .selectIcon(true)
        .onChange( () => {
          this.menuItemState = !this.menuItemState
        })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '绘制MenuItemGroup' })
        .selected(this.menuItemGroupState)
        .selectIcon(true)
        .onChange( () => {
          this.menuItemGroupState = !this.menuItemGroupState
        })
      if (this.menuItemGroupState) {
        MenuItemGroup({ header: '头标', footer: '尾标' }) {
          MenuItem({
            startIcon: this.iconStr,
            content: '菜单选项1',
            endIcon: this.iconStr2,
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: '菜单选项2',
            endIcon: this.iconStr2,
          })
        }
      }
      if (this.menuItemState) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      }
    }
    .backgroundColor('#B6C5D1')
    .borderWidth(1.0)
    .menuItemDivider({
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Pink,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value:2, unit: LengthUnit.VP}
    },)
    .menuItemGroupDivider({
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange,
      startMargin: {value: 2, unit: LengthUnit.VP},
      endMargin: {value: 2, unit: LengthUnit.VP}
    },)
  }

  // 多设备协同场景
  @Builder
  MenuBuilder_groupLayout() {
    Menu(){
      MenuItem({startIcon: $r('app.media.app_icon'), content: '菜单content'})
      MenuItemGroup_Comp()
    }
    .menuItemGroupDivider({
      strokeWidth: {value: 1.5, unit: LengthUnit.VP},
      color: Color.Orange})
  }

  // ForEach热更新菜单选项列表,菜单分割线绘制效果
  @State menuItemList: string[] = ['选项-0', '选项-1', '选项-2', '选项-3', '选项-4']
  @Builder
  MenuDividerBuilder_ForEachUpdateItem() {
    Menu() {
      ForEach(this.menuItemList, (menu: string, index: number): void => {
        MenuItem({content: menu})
      })
    }
    .menuItemDivider({
      startMargin: LengthMetrics.vp(15),
      endMargin: LengthMetrics.vp(15),
      strokeWidth: LengthMetrics.vp(2),
      color: Color.Green,
    })
  }
  @Builder
  MenuItemGroupDividerBuilder_ForEachUpdateItem() {
    Menu() {
      MenuItem({content: '菜单选项'})
      MenuItemGroup(){
        ForEach(this.menuItemList, (menu: string, index: number): void => {
          MenuItem({content: menu})
        })
      }
      MenuItem({content: '其他选项'})
    }
    .menuItemDivider({
      startMargin: LengthMetrics.vp(15),
      endMargin: LengthMetrics.vp(15),
      strokeWidth: LengthMetrics.vp(2),
      color: Color.Orange,
    })
    .menuItemGroupDivider({
      startMargin: LengthMetrics.vp(15),
      endMargin: LengthMetrics.vp(15),
      strokeWidth: LengthMetrics.vp(2),
      color: Color.Green,
    })
  }

  build() {
    Scroll(this.scroller){
      Column({space : 5}) {
        Text('验证特殊的Menu设置divider分割线').paramTextStyle()
        Column({space : 5}){
          Text(`空Menu的menuItemDivider | menuItemGroupDivider`).paramTextStyle()
          Text(`blankMenu: set_divider`)
            .componentTextStyle()
            .bindMenu(this.BlankMenu())
          Text(`一个Item的Menu的menuItemDivider | menuItemGroupDivider`).paramTextStyle()
          Text(`OneItemMenu: set_divider`)
            .componentTextStyle()
            .bindMenu(this.OneItemMenu())
          Text(`超多Item的Menu的menuItemDivider | menuItemGroupDivider`).paramTextStyle()
          Text(`MuchItemMenu: set_divider`)
            .componentTextStyle()
            .bindMenu(this.MuchItemsMenu())
          Text(`设padding的Menu的menuItemDivider | menuItemGroupDivider`).paramTextStyle()
          Text(`ItemMenu_setPadding: set_divider`)
            .componentTextStyle()
            .bindMenu(this.ItemMenu_Padding())
          Text(`If判断绘制MenuItem验证分隔线是否绘制`).paramTextStyle()
          Text(`ItemMenu_setIf: set_divider`)
            .componentTextStyle()
            .bindMenu(this.ItemMenu_If())

          Text(`模拟设备协同场景的菜单布局场景`).paramTextStyle()
          Text(`协同场景group菜单选项布局的分隔线`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_groupLayout())

          Text(`ForEach热更新菜单选项列表,菜单分割线绘制效果`).paramTextStyle()
          Text(`热更新菜单选项列表, Menu的分割线绘制`)
            .componentTextStyle()
            .bindMenu(this.menuShow[0]!!,this.MenuDividerBuilder_ForEachUpdateItem())
            .onClick(() => {
              this.menuShow[0] = true
              setTimeout(() => {
                this.menuItemList.splice(2,0, '新增选项')
              },4000)
            })
          Text(`热更新菜单选项列表, ItemGroup的分割线绘制`)
            .componentTextStyle()
            .bindMenu(this.menuShow[1]!!,this.MenuItemGroupDividerBuilder_ForEachUpdateItem())
            .onClick(() => {
              this.menuShow[1] = true
              setTimeout(() => {
                this.menuItemList.splice(2,0, '新增选项+')
              },4000)
            })
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