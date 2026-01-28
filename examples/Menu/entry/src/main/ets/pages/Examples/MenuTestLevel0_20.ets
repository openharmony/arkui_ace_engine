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
* 菜单边框外描边属性
*
 */

import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'


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


@Entry
@Component
struct MenuTestLevel0_20 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State show_1: boolean = false
  @State menuOption: ContextMenuOptions = {

  }

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
        Text(`验证菜单外描边属性的绘制`)
          .paramTextStyle()
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
          Text(`菜单箭头/R角`)
            .paramTextStyle()
          Select([
            { value:'不设置箭头/R角' },
            { value:'设置箭头/R角' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置箭头/R角':
                  this.menuOption = {
                  }
                  break;
                case '设置箭头/R角':
                  this.menuOption.enableArrow = true
                  this.menuOption.borderRadius = 8
                  break;
              }
            })
            .key('select_menuArrowRadiusBorder')
        }
        .columnStyle()
        Column({space: 5}){
          Text(`选择外描边属性的参数`)
            .paramTextStyle()
          Select([
            { value:'不设置外描边宽度/颜色' },
            { value:'设置外描边10px/橙色' },
            { value:'设置外描边10vp/橙色' },
            { value:'设置外描边负10vp/橙色' },
            { value:'设置外描边10fp/橙色' },
            { value:'设置外描边0vp/橙色' },
            { value:'设置外描边10lpx/橙色' },
            { value:'设置外描边10%/橙色' },
            { value:'设置外描边正常$r宽度/橙色' },
            { value:'设置外描边异常$r宽度/橙色' },
            { value:'设置外描边左边宽度10vp/橙色' },
            { value:'设置外描边四边不同宽度/橙色' },
            { value:'设置外描边四边正常+异常宽度/橙色' },  // 验证镜像化效果
            { value:'设置外描边2vp/Color橙色' },
            { value:'设置外描边20vp/颜色un' },
            { value:'设置外描边2vp/Str蓝色' },
            { value:'设置外描边20vp/UX默认值' },
            { value:'设置外描边2vp/Num绿色' },
            { value:'设置外描边2vp/Res紫色' },
            { value:'设置外描边2vp/Res异常' },
            { value:'设置外描边2vp/左边橙色' },
            { value:'设置外描边2vp/四边不同色' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置外描边宽度/颜色':
                  this.menuOption = {

                  }
                  break;
                case '设置外描边10px/橙色':
                  this.menuOption.outlineWidth = '10px'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边10vp/橙色':
                  this.menuOption.outlineWidth = '10vp'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边负10vp/橙色':
                  this.menuOption.outlineWidth = '-10vp'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边10fp/橙色':
                  this.menuOption.outlineWidth = '10fp'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边10lpx/橙色':
                  this.menuOption.outlineWidth = '10lpx'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边0vp/橙色':
                  this.menuOption.outlineWidth = '0vp'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边10%/橙色':
                  this.menuOption.outlineWidth = '10%'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边正常$r宽度/橙色':
                  this.menuOption.outlineWidth = $r('app.float.float_5')
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边异常$r宽度/橙色':
                  this.menuOption.outlineWidth = $r('app.media.app_icon')
                  this.menuOption.outlineColor = Color.Orange
                  break;

                case '设置外描边左边宽度10vp/橙色':
                  this.menuOption.outlineWidth = {
                    left: '10vp'
                    }
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边四边不同宽度/橙色':
                  this.menuOption.outlineWidth = {
                    left: '10vp', 
                    right: '10px', 
                    top: '10fp', 
                    bottom: '10lpx'
                    }
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边四边正常+异常宽度/橙色':
                  this.menuOption.outlineWidth = {
                    left: '5%', 
                    bottom: '-10vp', 
                    right: $r('app.media.app_icon'), 
                    top: $r('app.float.float_5')
                    }
                  this.menuOption.outlineColor = Color.Orange
                  break;

                case '设置外描边2vp/Color橙色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = Color.Orange
                  break;
                case '设置外描边20vp/颜色un':
                  this.menuOption.outlineWidth = '20vp'
                  this.menuOption.outlineColor = undefined
                  break;
                case '设置外描边2vp/Str蓝色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = 'rgba(10,89,247,1)'
                  break;
                case '设置外描边20vp/UX默认值':
                  this.menuOption.outlineWidth = '20vp'
                  this.menuOption.outlineColor = '#19ffffff'
                  break;
                case '设置外描边2vp/Num绿色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = 0x64BB5C
                  break;
                case '设置外描边2vp/Res紫色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = $r('app.color.Color_purple')
                  break;
                case '设置外描边2vp/Res异常':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = $r('app.media.app_icon')
                  break;
                case '设置外描边2vp/左边橙色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = {
                    left: Color.Orange
                    }
                  break;
                case '设置外描边2vp/四边不同色':
                  this.menuOption.outlineWidth = '2vp'
                  this.menuOption.outlineColor = {
                    left: Color.Orange, 
                    right: '#19ffffff',
                    top: 'rgba(10,89,247,1)', 
                    bottom: 0x64BB5C
                  }
                  break;
              }
            })
            .key('select_menuOutline')

          Text(`菜单: 外描边属性`)
            .componentTextStyle()
            .bindMenu(this.show!!, this.MenuBuilder(), this.menuOption)
            .onClick(() => {
              if ( !this.show ){
                this.show = true
              }
            })
          Text(`预览图菜单：外描边属性`)
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: MenuPreviewMode.IMAGE,
              outlineWidth: this.menuOption.outlineWidth,
              outlineColor: this.menuOption.outlineColor
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
    .backgroundColor('#b3525877')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}
