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
* 补充预览图菜单radius属性测试用例
* 验证bindContextMenu: 预览图不同尺寸: 预览图有尺寸限制/优先绘制菜,再绘制预览图
*/

import { LengthMetrics } from '@kit.ArkUI';
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'

class SizeOption {
  public width?: Length = '240'
  public height?: Length = '300'
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Select) function selectStyle() {
  .width('36%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_18 {
  scroller: Scroller = new Scroller()
  @State menuShow: boolean[] = [false, false, false]
  @State index: number[] = [0, 0, 0]
  @State previewBuilderSizeOptions: SizeOption = {
    width: 240,
    height: 160
  }

  //Menu菜单：设置不同的高度、宽度
  @Builder
  MenuBuilder_sized($$: SizeOption) {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .borderWidth(1.0)
    .height($$.height)
    .width($$.width)
  }

  //different size preview
  @Builder
  MenuPreviewBuilder($$: SizeOption) {
    Column(){
      Image($r('app.media.app_icon'))
    }
    .width($$.width).height($$.height)
  }

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  // 菜单预览图的radius
  @State contextMenuOption: ContextMenuOptions = {
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 3 }) {
        Text(`验证菜单预览图设置不同尺寸绘制效果`)
          .paramTextStyle()
        Column({space: 5}){
          Row({space: 3}){
            Select([
              { value:'W240' },
              { value:'W360' },
              { value:'W120' },
              { value:'W80%' },
            ])
              .selectStyle()
              .value('W240')
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'W240':
                    this.previewBuilderSizeOptions.width = 240
                    break;
                  case 'W360':
                    this.previewBuilderSizeOptions.width = 360
                    break;
                  case 'W120':
                    this.previewBuilderSizeOptions.width = 120
                    break;
                  case 'W80%':
                    this.previewBuilderSizeOptions.width = '80%'
                    break;
                }
              })
              .key('select_previewBuilderWidth')

            Select([
              { value:'H160' },
              { value:'H320' },
              { value:'H640' },
              { value:'H40%' },
            ])
              .selectStyle()
              .value('H160')
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'H160':
                    this.previewBuilderSizeOptions.height = 160
                    break;
                  case 'H320':
                    this.previewBuilderSizeOptions.height = 320
                    break;
                  case 'H640':
                    this.previewBuilderSizeOptions.height = 640
                    break;
                  case 'H40%':
                    this.previewBuilderSizeOptions.height = '40%'
                    break;
                }
              })
              .key('select_previewBuilderHeight')
          }

          Image($r('app.media.app_icon'))
            .key(`contextMenu: previewCustom`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[0], this.MenuBuilder_sized({width: 200}), {
              preview: this.MenuPreviewBuilder({
                width: this.previewBuilderSizeOptions.width,
                height: this.previewBuilderSizeOptions.height
              }),
              onDisappear: () => {
                this.menuShow[0] = false
              }
            })
            .onClick( () => {
              this.menuShow[0] = true
            })
        }
        .columnStyle()

        // api18属性
        Text(`验证菜单预览图设置不同radius绘制效果`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`菜单预览图设置IMAGE类型,设置固定的radius的绘制效果: 生效`)
            .paramTextStyle()
          Text(`预览图菜单: previewImage`)
            .height(75)
            .backgroundColor(Color.Orange)
            .padding(16)
            .bindContextMenu(this.menuShow[1], this.MenuBuilder(), {
              preview: MenuPreviewMode.IMAGE,
              previewBorderRadius: 5,

              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
            .onClick( () => {
              this.menuShow[1] = true
            })


          Text(`菜单预览图设置Custom类型,切换radius不同参数的绘制效果: 生效`)
            .paramTextStyle()
          Select([
            { value:'不设置预览图radius' },
            { value:'设置undefined' },
            { value:'设置length-24vp' },
            { value:'设置length-4' },
            { value:'设置length-24px' },
            { value:'设置length-50%' },
            { value:'设置length-res异常' },
            { value:'设置length-str异常' },
            { value:'设置length-num超大' },  // 预期走maxRadius的一般

            { value:'设置radius-缺省,正常' },
            { value:'设置radius-全部,正常' },
            { value:'设置radius-全部,混合' },

            { value:'设置localizedRadius-全部,正常' },  //测试镜像化
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置预览图radius':
                  this.contextMenuOption = {}
                  break;
                case '设置undefined':
                  this.contextMenuOption.previewBorderRadius = undefined
                  break;

                case '设置length-24vp':
                  this.contextMenuOption.previewBorderRadius = '24vp'
                  break;
                case '设置length-4':
                  this.contextMenuOption.previewBorderRadius = 4
                  break;
                case '设置length-24px':
                  this.contextMenuOption.previewBorderRadius = '24px'
                  break;
                case '设置length-50%':
                  this.contextMenuOption.previewBorderRadius = '50%'
                  break;
                case '设置length-res异常':
                  this.contextMenuOption.previewBorderRadius = $r('app.media.app_icon')
                  break;
                case '设置length-str异常':
                  this.contextMenuOption.previewBorderRadius = $r('app.string.app_name')
                  break;
                case '设置length-num超大':
                  this.contextMenuOption.previewBorderRadius = 60
                  break;

                case '设置radius-缺省,正常':
                  this.contextMenuOption.previewBorderRadius = {topLeft: 8}
                  break;
                case '设置radius-全部,正常':
                  this.contextMenuOption.previewBorderRadius = {
                    topLeft: 24,
                    topRight: 10,
                    bottomLeft: '24px',
                    bottomRight: '20%'}
                  break;
                case '设置radius-缺省,混合':
                  this.contextMenuOption.previewBorderRadius = {
                    topLeft: '-24',
                    topRight: '0',
                    bottomLeft: '24',
                    bottomRight: '36'
                  }
                  break;

                case '设置localizedRadius-全部,正常':
                  this.contextMenuOption.previewBorderRadius = {
                    topStart: LengthMetrics.vp(4),
                    topEnd: LengthMetrics.vp(8),
                    bottomStart: LengthMetrics.vp(12),
                    bottomEnd: LengthMetrics.vp(8),
                  }
                  break;
              }
            })
            .key('select_previewRadius')
          Image($r('app.media.app_icon'))
            .key(`contextMenu: previewRadius`)
            .width('120').height(60)
            .bindContextMenu(this.menuShow[2], this.MenuBuilder(), {
              preview: this.MenuPreviewBuilder({width: 160, height: 75}),
              previewBorderRadius: this.contextMenuOption.previewBorderRadius,

              onDisappear: () => {
                this.menuShow[2] = false
              }
            })
            .onClick( () => {
              this.menuShow[2] = true
            })

          Text(`菜单预览图设置Custom类型,设置radius的绘制效果,组合测试预览图scale和transition`)
            .paramTextStyle()
          Image($r('app.media.app_icon'))
            .key(`contextMenu: response_previewRadius_scale_transition`)
            .width('120').height(60)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder({width: 160, height: 75}),
              previewBorderRadius: {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(4),
                bottomStart: LengthMetrics.vp(12),
                bottomEnd: LengthMetrics.vp(8),
              },
              previewAnimationOptions: {
                scale: [0.9, 1.5],
                hoverScale: [0.6, 0.9],
                transition: TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Ease }).combine(
                  TransitionEffect.rotate({ x: 1, angle: 90 })),
              },
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