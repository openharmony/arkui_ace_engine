import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy,
  Provide
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Image,
  ImageAttribute,
  Grid,
  GridItem,
  GridAttribute,
  GridItemAttribute,
  Text,
  TextAttribute,
  Column,
  ColumnAttribute,
  Row,
  RowAttribute,
  Component,
  Reusable,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Scroller,
  Navigation,
  NavPathStack,
  NavPathInfo,
  Builder,
  Color,
  LazyForEach,
  ForEach
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import hiTraceMeter from '@ohos.hiTraceMeter';

import { routerParam, NavigationParam, pathStack } from './BaseDataMode'
import { AnimationTest } from './AnimationTest'
import { NodeContainerTest } from './NodeContainerTest'
import { IndexAccessibilityTest } from './IndexAccessibilityTest'
import { InspectorTest } from './InspectorTest'
import { Image001Test } from './Image001Test'
import { Image002Test } from './Image002Test'
import { ButtonTest } from './ButtonTest'
import { CheckboxTest } from './CheckboxTest'
import { CheckboxGroupTest } from './CheckboxGroupTest'
import { Grid001Test } from './Grid001Test'
import { Grid002Test } from './Grid002Test'
import { ResourceTest } from './ResourceTest'
import { SideBarTest } from './SideBarTest'
import { TextTest } from './TextTest'
import { TextInputTest } from './TextInputTest'
import { SearchTest } from './SearchTest'
import { VideoTest } from './VideoTest'
import { ShapeTest } from './ShapeTest'
import { StateLinkPropTest } from './StateLinkPropTest'
import { StorageLinkAndPropTest } from './StorageLinkAndPropTest'
import { ObservedObjectLinkTest } from './ObservedObjectLinkTest'
import { Layout001Test } from './Layout001Test'
import { Layout002Test } from './Layout002Test'
import { Layout003Test } from './Layout003Test'
import { LayoutPropTest } from './LayoutPropTest'
import { LayoutFunctionTest } from './LayoutFunctionTest'
import { MultiComponentTest } from './MultiComponentTest'
import { CanvasTest } from './CanvasTest'
import { PageOne, PageTwo, NavigationTest } from './NavigationTest'
import { BindSheetTest } from './BindSheetTest'
import { BindContentCoverTest } from './BindContentCoverTest'
import { RichEditorAddTest } from './RichEditorAddTest'
import { RichEditorDeleteTest } from './RichEditorDeleteTest'
import { RichEditorCopyPasteTest } from './RichEditorCopyPasteTest'
import { GestureTest } from './GestureTest'
import { PolymorphismTest } from './PolymorphismTest'
import { FocusTest } from './FocusTest'
import { GetHostContextTest } from './GetHostContextTest'
import { EmbeddedComponentTest } from './EmbeddedComponentTest'
import { UIExtensionComponentTest } from './UIExtensionComponentTest'

@Component
struct MyStateSample {
  scroller: Scroller = new Scroller()
  @State data: Array<string> = [
    '$r使用资源测试',
    'NodeContainer功能测试',
    '无障碍测试',
    'inspector接口测试',
    'Image支持$r显示图片',
    'Image支持网络图片图片',
    'Image支持BASE64字符串图片',
    'Button基础功能测试',
    'checkbox基础功能测试',
    'CheckboxGroup基础功能测试',
    'Grid基础功能用例001',
    'Grid基础功能用例002',
    'NodeContent挂载命令式节点',
    '动效测试001',
    '模态类组件测试001',
    '模态类组件测试002',
    '导航类组件测试001',
    '导航类组件测试002',
    'Text文本框用例001',
    'Search搜索框用例001',
    'TextInput文本输入框用例001',
    'Video组件基础功能测试用例',
    'Shape组件基础功能测试用例',
    'Canvas组件基础功能测试用例',
    'State/Prop/Link支持基础功能测试',
    'StorageLink/StorageProp支持基础功能观测',
    '@Observed/@ObjectLink支持基础功能观测能力',
    '布局基础功能测试用例001',
    '布局基础功能测试用例002',
    '布局基础功能测试用例003',
    '布局组件基础功能测试用例',
    '布局属性组件功能',
    '一多组布局属性组件功能',
    '富文本输入框用例001',
    '富文本输入框用例002',
    '富文本输入框用例003',
    '手势基础功能测试用例',
    '多态样式基础功能',
    '焦点按键基础功能',
    'getHostContext功能测试',
    'embeddedComponent功能测试',
    'UEC功能测试'
  ];

  @Builder
  PageBuilder(name: string, param: Object|null|undefined) {
    if (name == 'NodeContainer功能测试') {
      NodeContainerTest()
    } else if (name == '无障碍测试') {
      IndexAccessibilityTest()
    } else if (name == 'inspector接口测试') {
      InspectorTest()
    } else if (name === 'Image支持$r显示图片') {
      Image001Test()
    } else if (name === 'Image支持网络图片图片') {
      Image002Test()
    } else if (name === 'Image支持BASE64字符串图片') {
      
    } else if (name == 'Button基础功能测试') {
      ButtonTest()
    } else if (name == 'checkbox基础功能测试') {
      CheckboxTest()
    } else if (name == 'CheckboxGroup基础功能测试') {
      CheckboxGroupTest()
    } else if (name == 'Grid基础功能用例001') {
      Grid001Test()
    } else if (name == 'Grid基础功能用例002') {
      Grid002Test()
    } else if (name == '$r使用资源测试') {
      ResourceTest()
    } else if (name == 'NodeContent挂载命令式节点') {

    } else if (name == '动效测试001') {
      AnimationTest()
    } else if (name == '模态类组件测试001') {
      BindSheetTest()
    } else if (name == '模态类组件测试002') {
      BindContentCoverTest()
    } else if (name == '导航类组件测试001') {
      NavigationTest()
    } else if (name == '导航类组件测试002') {
      SideBarTest()
    } else if (name == 'Text文本框用例001') {
      TextTest()
    } else if (name == 'Search搜索框用例001') {
      SearchTest()
    } else if (name == 'TextInput文本输入框用例001') {
      TextInputTest()
    } else if (name == 'Video组件基础功能测试用例') {
      VideoTest()
    } else if (name == 'Shape组件基础功能测试用例') {
      ShapeTest()
    } else if (name == 'Canvas组件基础功能测试用例') {
      CanvasTest()
    } else if (name == 'State/Prop/Link支持基础功能测试') {
      StateLinkPropTest()
    } else if (name == 'StorageLink/StorageProp支持基础功能观测') {
      StorageLinkAndPropTest()
    } else if ( name == '@Observed/@ObjectLink支持基础功能观测能力') {
      ObservedObjectLinkTest()
    } else if (name == '布局基础功能测试用例001') {
      Layout001Test()
    } else if (name == '布局基础功能测试用例002') {
      Layout002Test()
    } else if (name == '布局基础功能测试用例003') {
      Layout003Test()
    } else if (name == '布局组件基础功能测试用例') {
      LayoutFunctionTest()
    } else if (name == '布局属性组件功能') {
      LayoutPropTest()
    } else if (name == '一多组布局属性组件功能') {
      MultiComponentTest()
    } else if (name == 'pageOne') {
      PageOne()
    } else if (name == 'pageTwo') {
      PageTwo()
    } else if (name == '富文本输入框用例001') {
      RichEditorAddTest()
    } else if (name == '富文本输入框用例002') {
      RichEditorDeleteTest()
    } else if (name == '富文本输入框用例003') {
      RichEditorCopyPasteTest()
    } else if (name == '手势基础功能测试用例') {
      GestureTest()
    } else if (name == '多态样式基础功能') {
      PolymorphismTest()
    } else if (name == '焦点按键基础功能') {
      FocusTest()
    } else if (name == 'getHostContext功能测试') {
      GetHostContextTest()
    } else if (name == 'embeddedComponent功能测试') {
      EmbeddedComponentTest()
    } else if (name == 'UEC功能测试') {
      UIExtensionComponentTest()
    }
  }

  build() {
    Navigation(pathStack) {
      Column(undefined) {
        Grid(undefined, undefined) {
          ForEach(this.data, (item: string, index: number): void => {
            GridItem(undefined) {
              Button(item)
                .width('100%')
                .height(44)
                .onClick((e?: ClickEvent) => {
                  let info: NavPathInfo = new NavPathInfo(item, new NavigationParam('this is push ' + item))
                  pathStack.pushPath(info, undefined)
                })
            }
            .width('80%')
            .height(80)
          }, (item: string, index: number): string => JSON.stringify(item.valueOf())
          )
        }
        .height('100%')
        .columnsTemplate('1fr 1fr')
        .columnsGap(0)
        .rowsGap(0)
        .clip(true)
      }
    }.navDestination(this.PageBuilder)
    .title('强基用例L0 Demo')
  }
}

export class ComExampleTrivialApplication extends UserView {
  getBuilder() {
    hilog.info(0x0000, 'testTag', 'getBuilder');
    let wrapper = @memo () => {
      hilog.info(0x0000, 'testTag', 'MyStateSample');
      MyStateSample(undefined)
    }
    return wrapper
  }
}