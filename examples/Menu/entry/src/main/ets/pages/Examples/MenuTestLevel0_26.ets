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

// xxx.ets
/*
* 菜单控制opt属性systemMaterial 测试用例
* 1、数据类型设置不同参数
* 2、组合测试：不同次级菜单/ 模糊材质/ 背景色/ 箭头/ 描边
*
 */
import { inputMethod } from '@kit.IMEKit';
import { MyComponent } from '../../common/MyComponent'
import { SimpleMenuBuilder, MenuAttrOptions } from  '../../customBuilder/MenuBuilder'
import { uiMaterial } from '@kit.ArkUI';

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_26 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  // 菜单避让边框安全距离
  @State bindMenuEdgeSafePadding: Padding = {left: 16, right: 16, top: 0, bottom: 0}
  @State bindContextMenuEdgeSafePadding: Padding = {left: 16, right: 16, top: 16, bottom: 4}

  // 不同菜单类型
  @State bindMode: string = 'bindMenu'

  // 菜单出现位置
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start

  //
  @State menuShow: boolean[] = [false, false]

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: SubMenuExpandingMode.STACK_EXPAND
  }
  @Builder
  MenuBuilder() {
    SimpleMenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  // 菜单控制的opt
  @State contextMenuOptions: ContextMenuOptions = {
  }
  // systemMaterial 测试参数

  @State systemMaterialInfo: string = '菜单不设置系统材质'
  @State systemMaterialList:  Array<SystemUiMaterial | undefined> = new Array<SystemUiMaterial | undefined> (
     undefined,
     new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }),
     new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
   )


  // 菜单的预览图
  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(120)
      .height(60)
  }

  build() {
      // 控制区域
      Scroll(this.scroller){
        Column({space: 5}) {
          Text('菜单systemMaterial效果')
            .paramTextStyle()
          Column({space: 5}){
            Text('选择验证的菜单').paramTextStyle()
            Select([
              {value: 'bindMenu'},
              {value: '预览图菜单'}
            ])
              .selectStyle()
              .id('select_bind_mode')
              .value(this.bindMode!!)
              .onSelect((index: number, value:string) => {
                this.bindMode = value
              })
            Text(`切换次级菜单类型`)
              .paramTextStyle()
            Row({space: 3}){
              MyComponent({title: 'SIDE', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.SIDE_EXPAND
              }})
              MyComponent({title: 'EMBEDDED', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.EMBEDDED_EXPAND
              }})
              MyComponent({title: 'STACK', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.STACK_EXPAND
              }})
            }
          }
          .columnStyle()

          Column({space: 5}){
            Text('选择菜单systemMaterial参数, 验证设置不同MaterialType材质的菜单效果')
              .paramTextStyle()
            Select([
              {value: 'undefined'},
              {value: 'MaterialType.NONE'},
              {value: 'MaterialType.SEMI_TRANSPARENT'},
            ])
              .selectStyle()
              .value(this.systemMaterialInfo!!)
              .id('select_systemMaterial')
              .onSelect((index: number, value:string) => {
                this.systemMaterialInfo = value
                this.contextMenuOptions.systemMaterial = this.systemMaterialList[index]
              })

            if (this.bindMode === 'bindMenu') {
              Text('bindMenu的系统材质视效')
                .componentTextStyle()
                .bindMenu(this.MenuBuilder(), {
                  placement: Placement.Top,
                  systemMaterial: this.contextMenuOptions.systemMaterial
                })
            } else {
              Text('预览图菜单的系统材质视效')
                .componentTextStyle()
                .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                  placement: Placement.Top,
                  preview: this.MenuPreviewBuilder(),
                  systemMaterial: this.contextMenuOptions.systemMaterial
                })
            }

            Text('验证菜单系统材质组合设置其他属性的绘制效果')
              .paramTextStyle()
            if (this.bindMode === 'bindMenu') {
              Text('bindMenu的无系统材质+组合视效')
                .componentTextStyle()
                .bindMenu(this.MenuBuilder(), {
                  placement: Placement.Top,

                  backgroundColor: Color.Orange,
                  outlineWidth: 2,
                  outlineColor: Color.Blue,
                })
              Text('bindMenu的系统材质+组合视效')
                .componentTextStyle()
                .bindMenu(this.MenuBuilder(), {
                  placement: Placement.Top,

                  backgroundColor: Color.Orange,
                  outlineWidth: 2,
                  outlineColor: Color.Blue,
                  systemMaterial:   new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
                })

            } else {
              Text('预览图菜单的无系统材质+组合视效')
                .componentTextStyle()
                .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                  placement: Placement.Top,
                  preview: this.MenuPreviewBuilder(),

                  backgroundColor: Color.Orange,
                  outlineWidth: 2,
                  outlineColor: Color.Blue,
                })
              Text('预览图菜单的系统材质+组合视效')
                .componentTextStyle()
                .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                  placement: Placement.Top,
                  preview: this.MenuPreviewBuilder(),

                  backgroundColor: Color.Orange,
                  outlineWidth: 2,
                  outlineColor: Color.Blue,
                  systemMaterial:    new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
                })
            }
          }
          .columnStyle()

        }
        .width('100%')
      }
      .padding(10)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
  }

  //进入该界面没有跳转延迟
  pageTransition() {
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }

}