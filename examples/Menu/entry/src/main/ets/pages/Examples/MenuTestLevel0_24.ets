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
 * bindContextMenu设置预览图菜单
 * 预览图菜单的预览图缩放方式/预览图宽高布局区域
 */

import { MyComponent } from '../../common/MyComponent'
import { SimpleMenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .borderWidth(1.0)
  .padding(5)
}

@Extend(Select)
function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_24 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State menuOption: ContextMenuOptions = {}
  //column的对齐方式
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start
  //
  @State menuShow: boolean[] = [false, false]
  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }
  @State menuBuilderWidth: number = 160
  @State menuBuilderHeight: number = 120

  @Builder
  MenuBuilder() {
    SimpleMenuBuilder({ menuAttrOptions: { submenuMode: this.menuAttrOption.submenuMode } })
      .width(this.menuBuilderWidth)
      .height(this.menuBuilderHeight)
  }

  // 菜单的预览图
  @State previewWidth: number | string = 120
  @State previewHeight: number | string = 120

  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(this.previewWidth)
      .height(this.previewHeight)
  }

  // 菜单控制的opt
  @State contextMenuOptions: ContextMenuOptions = {}

  build() {
    Stack() {
      // bindMenu绑定组件区域
      Scroll() {
        Column() {
          Column() {
          }
          .backgroundColor('#ff848f6b')
          .height(20).width(20)
          .bindContextMenu(this.menuShow[0], this.MenuBuilder(), {
            previewScaleMode: this.menuOption.previewScaleMode,
            availableLayoutArea: this.menuOption.availableLayoutArea,
            layoutRegionMargin: this.contextMenuOptions.layoutRegionMargin,
            preview: this.MenuPreviewBuilder(),
            onDisappear: () => {
              this.menuShow[0] = false
            }
          })
        }
        .alignItems(this.columnAlignHorizontal)
        .justifyContent(this.columnAlignFlex)
        .width('100%').height('100%')
      }
      .padding({
        top: 10,
        bottom: 10,
        left: 16,
        right: 16
      })
      .width('100%')
      .height('100%')
      .backgroundColor(Color.Transparent)

      // 控制区域
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text('验证菜单预览图')
            .paramTextStyle()
          Column({ space: 5 }) {
            Text(`切换绑定组件的位置`)
              .paramTextStyle()
            Select([
              { value: 'TopStart' },
              { value: 'TopCenter' },
              { value: 'TopEnd' },
              { value: 'CenterStart' },
              { value: 'Center' },
              { value: 'CenterEnd' },
              { value: 'BottomStart' },
              { value: 'BottomCenter' },
              { value: 'BottomEnd' },
            ])
              .value('TopStart')
              .selected(0)
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'TopStart':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'TopCenter':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'TopEnd':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                  case 'CenterStart':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'Center':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'CenterEnd':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                  case 'BottomStart':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'BottomCenter':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'BottomEnd':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                }
              })
              .key('select_targetCompPos')
            Text(`切换次级菜单类型: ${this.menuAttrOption.submenuMode}`)
              .paramTextStyle()
            Row({ space: 3 }) {
              MyComponent({
                title: 'SIDE', func: () => {
                  this.menuAttrOption.submenuMode = SubMenuExpandingMode.SIDE_EXPAND
                }
              })
              MyComponent({
                title: 'EMBEDDED', func: () => {
                  this.menuAttrOption.submenuMode = SubMenuExpandingMode.EMBEDDED_EXPAND
                }
              })
              MyComponent({
                title: 'STACK', func: () => {
                  this.menuAttrOption.submenuMode = SubMenuExpandingMode.STACK_EXPAND
                }
              })
            }

            Text(`切换菜单预览图宽度: ${this.previewWidth}`)
              .paramTextStyle()
            Select([
              { value: '80%' },
              { value: '85%' },
              { value: '90%' },
              { value: '95%' },
              { value: '100%' },
              { value: '120' },
              { value: '240' },
              { value: '320' },
              { value: '400' },
            ])
              .selected(4)
              .selectStyle()
              .onSelect((idx, value: string) => {
                this.previewWidth = value
              })
              .key('select_menuPreviewWidth')
            Text(`切换菜单预览图高度: ${this.previewHeight}`)
              .paramTextStyle()
            Select([
              { value: '80%' },
              { value: '85%' },
              { value: '90%' },
              { value: '95%' },
              { value: '100%' },
              { value: '120' },
              { value: '240' },
              { value: '480' },
              { value: '600' },
              { value: '840' },
            ])
              .selected(4)
              .selectStyle()
              .onSelect((idx, value: string) => {
                this.previewHeight = value
              })
              .key('select_menuPreviewHeight')
            Text(`切换菜单宽度: ${this.menuBuilderWidth}`)
              .paramTextStyle()
            Slider({
              value: this.menuBuilderWidth!!,
              min: 120,
              max: 240,
              step: 20
            })
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.menuBuilderWidth = value
              })
              .id('sliderMenuBuilderWidth')
            Text(`切换菜单高度: ${this.menuBuilderHeight}`)
              .paramTextStyle()
            Slider({
              value: this.menuBuilderHeight!!,
              min: 80,
              max: 240,
              step: 40
            })
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.menuBuilderHeight = value
              })
              .id('sliderMenuBuilderHeight')
            Text(`切换预览图的安全边距: ${this.contextMenuOptions.layoutRegionMargin}`)
              .paramTextStyle()
            Row({ space: 3 }) {
              MyComponent({
                title: '默认边界边距', func: () => {
                  this.contextMenuOptions.layoutRegionMargin = undefined
                }
              })
              MyComponent({
                title: 'margin: 60', func: () => {
                  this.contextMenuOptions.layoutRegionMargin = {
                    top: 60,
                    bottom: 60,
                    left: 60,
                    right: 60
                  }
                }
              })
            }
          }
          .columnStyle()

          Column({ space: 5 }) {
            Text(`选择预览图缩放模式`)
              .paramTextStyle()
            Select([
              { value: 'PreviewScaleMode.AUTO' },
              { value: 'PreviewScaleMode.CONSTANT' },
              { value: 'PreviewScaleMode.MAINTAIN' },
            ])
              .selected(0)
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'PreviewScaleMode.AUTO':
                    this.menuOption.previewScaleMode = PreviewScaleMode.AUTO
                    break;
                  case 'PreviewScaleMode.CONSTANT':
                    this.menuOption.previewScaleMode = PreviewScaleMode.CONSTANT
                    break;
                  case 'PreviewScaleMode.MAINTAIN':
                    this.menuOption.previewScaleMode = PreviewScaleMode.MAINTAIN
                    break;
                }
              })
              .key('select_menuPreviewScaleMode')
            Text(`选择预览图宽高的可布局区域`)
              .paramTextStyle()
            Select([
              { value: 'undefined' },
              { value: 'AvailableLayoutArea.SAFE_AREA' },
            ])
              .selected(0)
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'undefined':
                    this.menuOption.availableLayoutArea = undefined
                    break;
                  case 'AvailableLayoutArea.SAFE_AREA':
                    this.menuOption.availableLayoutArea = AvailableLayoutArea.SAFE_AREA
                    break;
                }
              })
              .key('select_menuAvailableLayoutArea')
            Text('预览图菜单')
              .componentTextStyle()
              .onClick(() => {
                this.menuShow[0] = true
              })
          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding(24)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .alignContent(Alignment.Center)
    .width('100%')
    .height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}