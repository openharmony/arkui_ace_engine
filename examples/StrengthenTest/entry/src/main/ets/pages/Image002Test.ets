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
  $r,
  Entry,
  Text,
  TextAttribute,
  ResourceColor,
  Color,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Font,
  Progress,
  ProgressAttribute,
  ProgressType,
  ProgressOptions,
  ProgressStatus,
  RingStyleOptions,
  LinearStyleOptions,
  ProgressStyleOptions,
  CapsuleStyleOptions,
  ScaleRingStyleOptions,
  ScanEffectOptions,
  QRCode,
  QRCodeAttribute,
  LoadingProgress,
  LoadingProgressAttribute,
  PatternLock,
  PatternLockAttribute,
  Badge,
  BadgeAttribute,
  BadgeStyle,
  BadgeParam,
  BadgeParamWithNumber,
  BadgeParamWithString,
  DataPanel,
  DataPanelAttribute,
  DataPanelType,
  DataPanelOptions,
  Gauge,
  GaugeAttribute,
  GaugeOptions,
  ColorStop,
  LinearGradient,
  TextTimer,
  TextTimerController,
  TextTimerOptions,
  TextTimerAttribute,
  TextClock,
  TextClockAttribute,
  Image,
  ImageAttribute,
  Flex,
  FlexAttribute,
  Row,
  RowAttribute,
  Alignment,
  PixelMap,
  ResizableOptions,
  EdgeWidths,
  NavDestination, 
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'

import hilog from '@ohos.hilog'
import image from '@ohos.multimedia.image'

@Component
export struct Image002Test {
  @State pixelmap: PixelMap | string = ''

  aboutToAppear() {
    // 从配置文件或数据库中读取图片地址
    this.pixelmap = this.getConfiguredImageUrl();
  }

  getConfiguredImageUrl(): string {
    return ''
  }

  build() {
    NavDestination() {
      
    }
    .title('Image支持网络图片图片')
  }
}