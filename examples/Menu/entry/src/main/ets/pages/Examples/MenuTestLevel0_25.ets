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
* 混合手势菜单 测试用例
* 1、验证入参content设置un的菜单弹出效果：预期不弹出
* 2、验证入参content设置正常CustomBuilderT, 动态切换不同options参数类型，菜单功能实现
*
 */

import { MyComponent } from '../../common/MyComponent'
import { SimpleMenuBuilder, MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'


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
struct MenuTestLevel0_25 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  @State contextMenuOpt: ContextMenuOptions = {

  }

  @Builder
  MenuWithResponseBuilder(type: ResponseType) {
    Column({space: 5}){
      if (type === ResponseType.RightClick) {
        Text('右击菜单类型')
      } else if (type === ResponseType.LongPress) {
        Text('长按菜单类型')
      }
      SimpleMenuBuilder()
    }
    .padding(10)
  }

  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(160).height(120)
  }

  build() {
    Scroll(this.scroller) {
      Column({space: 5}){
        Text('验证混合手势菜单功能').paramTextStyle()
        Column({space: 5}){
          Text('混合手势菜单content设置un')
            .paramTextStyle()
          Text('混合手势菜单content设置un')
            .componentTextStyle()
            .bindContextMenuWithResponse(undefined)

          Text('切换混合手势菜单opt设置不同参数')
            .paramTextStyle()

          Select([
            {value: 'opt设置为{}'},
            {value: 'opt设置placement'},
            {value: 'opt设置preview'},
            {value: 'opt设置preview动效'},
          ])
            .id('select_bnd_options')
            .onSelect((index: number, value: string) => {
              switch (value) {
                case 'opt设置为{}':
                  this.contextMenuOpt = {}
                  break;
                case 'opt设置placement':
                  this.contextMenuOpt = {
                    placement: Placement.Bottom
                  }
                  break;
                case 'opt设置preview':
                  this.contextMenuOpt = {
                    preview: () => {
                      return this.MenuPreviewBuilder()
                    },
                  }
                  break;
                case 'opt设置preview动效':
                  this.contextMenuOpt = {
                    preview: () => {
                      return this.MenuPreviewBuilder()
                    },
                    previewAnimationOptions: {
                      scale: [0.8, 1.5],
                      hoverScale: [0.5, 0.8],
                      hoverScaleInterruption: true
                    }
                  }
                  break;

                default:
                  break;
              }
            })
          Text('混合手势菜单切换opt参数')
            .componentTextStyle()
            .bindContextMenuWithResponse(this.MenuWithResponseBuilder, this.contextMenuOpt)
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