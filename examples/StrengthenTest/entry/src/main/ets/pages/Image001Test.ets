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
export struct Image001Test {
  build() {
    NavDestination() {
      Column() {
        Row() {
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .borderWidth(1)
            .borderColor(Color.Blue)
        }
      }
    }
    .title('Image支持$r显示图片')
  }
}
