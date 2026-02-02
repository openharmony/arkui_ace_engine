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
* UEC场景/ 菜单蒙层测试用例
*
 */

import { MyComponent } from '../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../customBuilder/MenuBuilder'


@Extend(Text) function paramTextStyle() {
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
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Builder
export function MenuTestLevel0_0_UEC_Builder(){
  MenuTestLevel0_0_UEC()
}


@Preview
@Component
export struct Menu_UEC_0 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State menuOption: ContextMenuOptions = {
  }
  @State showInSubWindow: boolean = true
  // menuBuilder
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 1
  }
  @Builder
  MenuBuilder() {
    MenuBuilder({
        menuAttrOptions: this.menuAttrOption
        })
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证菜单蒙层属性的绘制/模态模式的效果`)
          .paramTextStyle()
        Column({space: 3}){
          Text(`区域外的事件Toast`)
            .componentTextStyle()
            .onClick(() => {
              this.getUIContext().getPromptAction().openToast({
                message: '区域外事件响应弹出toast',
                duration: 3000
              })
            })
        }
        .columnStyle()
        Column({space: 5}){
          Text(`切换次级菜单类型: ${this.menuAttrOption.submenuMode}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'SIDE', func: () => {
              this.menuAttrOption.submenuMode = 0
            }})
            MyComponent({title: 'EMBEDDED', func: () => {
              this.menuAttrOption.submenuMode = 1
            }})
            MyComponent({title: 'STACK', func: () => {
              this.menuAttrOption.submenuMode = 2
            }})
          }

          Text(`切换菜单子窗类型: ${this.showInSubWindow}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'True', func: () => {
              this.showInSubWindow = true
            }})
            MyComponent({title: 'False', func: () => {
              this.showInSubWindow = false
            }})
          }
        }
        .columnStyle()
        Column({space: 5}){
          Text(`选择菜单蒙层`)
            .paramTextStyle()
          Select([
            { value:'不设置蒙层属性' },
            { value:'设置蒙层true' },
            { value:'设置蒙层false' },
            { value:'设置蒙层un' },
            { value:'设置蒙层空maskType' },
            { value:'设置蒙层正常maskType' },
            { value:'设置蒙层异常maskType' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置蒙层属性':
                  this.menuOption = {
                  }
                  break;
                case '设置蒙层true':
                  this.menuOption.mask = true
                  break;
                case '设置蒙层false':
                  this.menuOption.mask = false
                  break;
                case '设置蒙层un':
                  this.menuOption.mask = undefined
                  break;
                case '设置蒙层空maskType':
                  this.menuOption.mask = {

                  }
                  break;
                case '设置蒙层正常maskType':
                  this.menuOption.mask = {
                    color: '#660A59F7',
                    backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN
                  }
                  break;
                case '设置蒙层异常maskType':
                  this.menuOption.mask = {
                    color: '#660A59F7',
                    backgroundBlurStyle: undefined
                  }
                  break;

              }
            })
            .key('select_menuMask')

          Text(`选择菜单的模态模式`)
            .paramTextStyle()
          Select([
            { value:'ModalMode_AUTO' },
            { value:'ModalMode_NONE' },
            { value:'ModalMode_TARGET' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'ModalMode_AUTO':
                  this.menuOption.modalMode = ModalMode.AUTO
                  break;
                case 'ModalMode_NONE':
                  this.menuOption.modalMode = ModalMode.NONE
                  break;
                case 'ModalMode_TARGET':
                  this.menuOption.modalMode = ModalMode.TARGET_WINDOW
                  break;
              }
            })
            .key('select_menuModal')

          Text(`bindMenu: mask/modal`)
            .componentTextStyle()
            .bindMenu(this.show!!, this.MenuBuilder(), {
              showInSubWindow: this.showInSubWindow,

              mask: this.menuOption.mask,
              modalMode: this.menuOption.modalMode
            })
            .onClick(() => {
              if ( !this.show ){
                this.show = true
              }
            })
          Text(`contextMenu: mask/modal`)
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: MenuPreviewMode.IMAGE,
              mask: this.menuOption.mask,
              modalMode: this.menuOption.modalMode
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

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}

@Preview
@Component
export struct MenuTestLevel0_0_UEC {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, ]

  build() {
    NavDestination() {
      Scroll(this.scroller){
        Menu_UEC_0()
          .width('100%')
      }
      .padding(12)
      .scrollBar(BarState.Off)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .title('Menu基础功能_UEC场景菜单蒙层')
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
