import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Callback,
  Matrix2D,
  Path2D,
  CanvasFillRule,
  PixelMap,
  LengthMetricsUnit,
  Stack,
  OffscreenCanvasRenderingContext2D,
  DrawingRenderingContext,
  DragItemInfo,
  CustomBuilder,
  DragEvent,
  ImageAnalyzerController,
  ImageAnalyzerConfig,
  ImageAnalyzerType,
  ImageAIOptions,
  ImageData,
  ImageBitmap,
  Entry,
  OffscreenCanvas,
  Canvas,
  CanvasRenderingContext2D,
  RenderingContextSettings,
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
  NavDestinationContext
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Entry
@Component
export struct CanvasTest {


  build() {
    NavDestination() {
    }
    .title('Canvas组件基础功能测试用例')
  }
}
