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
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Length,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback,
  PixelMap,
  Image,
  ImageAttribute,
  Circle,
  CircleOptions,
  CircleAttribute,
  Ellipse,
  EllipseOptions,
  EllipseAttribute,
  Rect,
  RectOptions,
  RectAttribute,
  Path,
  PathOptions,
  PathAttribute,
  CanvasAttribute,
  VoidCallback, 
  Canvas, 
  CanvasRenderingContext2D, 
  RenderingContextSettings, 
  Scroll, 
  ScrollOptions, 
  ScrollAttribute, 
  Line, 
  LineOptions, 
  LineAttribute, 
  LineCapStyle, 
  LineJoinStyle, 
  Shape, 
  ShapeAttribute, 
  PolygonOptions, 
  PolygonAttribute,
  Polygon,
  Polyline,
  PolylineOptions,
  PolylineAttribute
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct ShapeTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  changeValue() {
    this.stateVar+='~'
  }
  @State f: boolean = false;

  build() {
    NavDestination() {
      Column(undefined) {
        Text(this.stateVar)

        Circle({ width: 100, height: 80 } as CircleOptions).fill(0xff00ff00)

        Ellipse({ width: '400vp', height: 80 }).fill(0xff00ff00)

        Rect({ width: 150, height: 80 } as RectOptions)
          .fill(0xff00ff00)
      }
    }
    .title('Shape组件基础功能测试用例')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
