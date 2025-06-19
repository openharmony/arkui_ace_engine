import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Margin,
  PlaybackSpeed,
  Row,
  RowOptions,
  RowAttribute,
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback,
  $r,
  VoidCallback,
  ImageFit,
  SeekMode,
  PlaybackInfo,
  FullscreenInfo,
  PreparedInfo,
  PixelMap,
  Video,
  VideoOptions,
  VideoAttribute,
  VideoController,
  PlaybackSpeed
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'


@Component
export struct VideoTest {
  private btnWidth: string = '40%';
  private btnHeight: number = 40;
  private btnMargin: Margin = {top: 5, left: 10} as Margin;
  private fontSize: number = 30;
  controller: VideoController = new VideoController()
  build() {
    NavDestination() {
      Column(undefined) {
        Video({
          src: $r('app.media.trailer'),
          previewUri: $r('app.media.startIcon'),
          controller: this.controller,
        } as VideoOptions)
          .width('90%')
          .height(400)

        Row(undefined) {
          Button('start')
            .margin(this.btnMargin)
            .width(this.btnWidth)
            .height(this.btnHeight)
            .fontSize(this.fontSize)
            .onClick((e: ClickEvent) => {
              this.controller.start();
            })
          Button('pause')
            .margin(this.btnMargin)
            .width(this.btnWidth)
            .height(this.btnHeight)
            .fontSize(this.fontSize)
            .onClick((e: ClickEvent) => {
              this.controller.pause();
            })
        }

        Row(undefined) {
          Button('stop')
            .margin(this.btnMargin)
            .width(this.btnWidth)
            .height(this.btnHeight)
            .fontSize(this.fontSize)
            .onClick((e: ClickEvent) => {
              this.controller.stop();
            })
        }
      }
      .width('100%')
    }
    .title('Video组件基础功能测试用例')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
