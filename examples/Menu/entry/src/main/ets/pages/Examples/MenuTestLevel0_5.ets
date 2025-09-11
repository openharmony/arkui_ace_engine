/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
/
* 
* 验证bindMenu的箭头绘制
* 验证bindContextMenu的enableArrow | arrowOffset
*
 */
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'


@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .borderWidth(1.0)
  .backgroundColor(Color.Orange)
  .textAlign(TextAlign.Center)
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
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_5 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  private bindContextMenuArrowList: ContextMenuOptions[] = [
  //1
    {},
    //2
    {
      enableArrow: undefined, //预期不设置箭头
    },
    //3
    {
      enableArrow: true,

    },
    //4
    {
      enableArrow: false
    },
    //5
    {
      enableArrow: true,
      arrowOffset: undefined,
    },
    //6
    {
      enableArrow: true,
      arrowOffset: '-60',
    },
    //7
    {
      enableArrow: true,
      arrowOffset: 0,
    },
    //8
    {
      enableArrow: true,
      arrowOffset: 30,
    },
    //9
    {
      enableArrow: true,
      arrowOffset: 300,
    },
    //10
    {
      enableArrow: true,
      arrowOffset: '30%',
    },
    //11
    {
      enableArrow: true,
      arrowOffset: $r('app.string.EntryAbility_label'), //预期居左对齐
    },

  ]

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  build() {
    Scroll(this.scroller) {
      Column({space: 5}){
        Text(`验证bindMenu/bindContextMenu的箭头绘制`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换次级菜单类型`)
            .paramTextStyle()
          Select([
            { value:'SIDE' },
            { value:'EMBEDDED' },
            { value:'STACK' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'SIDE':
                  this.menuAttrOption.submenuMode = 0
                  break;
                case 'EMBEDDED':
                  this.menuAttrOption.submenuMode = 1
                  break;
                case 'STACK':
                  this.menuAttrOption.submenuMode = 2
                  break;

              }
            })
            .key('select_subMenuMode')
        }
        .columnStyle()
        Column({ space: 3 }) {
          Text(`切换Arrow参数`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.bindContextMenuArrowList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.bindContextMenuArrowList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.bindContextMenuArrowList.length - 1
                }
              }
            })
          }

          Text('bindContextMenu: arrow')
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              enableArrow: this.bindContextMenuArrowList[this.index[0]].enableArrow,
              arrowOffset: this.bindContextMenuArrowList[this.index[0]].arrowOffset,
            })

          Text(`bindMenu: arrow`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
              enableArrow: this.bindContextMenuArrowList[this.index[0]].enableArrow,
              arrowOffset: this.bindContextMenuArrowList[this.index[0]].arrowOffset,
            })
        }
        .columnStyle()

        Text(`预览图菜单设置箭头, 预期不显示`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`预览图菜单：设置箭头`)
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              enableArrow: true,
              preview: MenuPreviewMode.IMAGE
            })
          Text(`bM设置Image：设置箭头`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
              enableArrow: true,
              preview: MenuPreviewMode.IMAGE
            })
        }
        .columnStyle()

        Text(``)
          .paramTextStyle()
      }
      .width('100%')
    }
    .backgroundColor('#B6C5D1')
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}