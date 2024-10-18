/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function listItemSwipeActionTest() {
  /*
* ListItem组件 swipeAction属性
* 找到画面id为listItemSwipeAction1,listItemSwipeAction2,listItemSwipeAction3的ListItem组件
* 找到画面文本为ListItemSwipeAction的button组件
* 获取listItem1的swipeAction属性与期待值"item",56,"YES","YES","YES","YES"比对
* 获取listItem2的swipeAction属性与期待值"item","item"比对
* 获取listItem3的swipeAction属性与期待值"item","item","NO","NO","NO","NO"比对
* 点击button，变更listItem3的selected属性值为"item",$r('app.string.length'),"OR","OR","OR","OR"
* 获取listItem2的selected属性与期待值"item",$r('app.string.length'),"OR","OR","OR","OR"比对
*/
  defineTest('listItemSwipeActionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("listItemSwipeActionTestDemo running")
    let driver: Tester = Tester.create()
    let listItem1: Component = await driver.findComponent(Matcher.create().id('listItemSwipeAction1').enabled(true))
    let listItem2: Component = await driver.findComponent(Matcher.create().id('listItemSwipeAction2').enabled(true))
    let listItem3: Component = await driver.findComponent(Matcher.create().id('listItemSwipeAction3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListItemSwipeAction').enabled(true))

    let swipeAction1: string = await listItem1.getInspectorInfo()
    assertFalse(JSON.parse(swipeAction1).$attrs.swipeAction.start == undefined)
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .builder
      .CustomBuilder, "item")
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .actionAreaDistance, 56)
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .onAction, "YES")
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .onEnterActionArea, "YES")
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .onExitActionArea, "YES")
    assertEqual(JSON.parse(swipeAction1)
      .$attrs
      .swipeAction
      .start
      .onStateChange, "YES")
    let swipeAction2: string = await listItem2.getInspectorInfo()
    assertEqual(JSON.parse(swipeAction2)
      .$attrs
      .swipeAction
      .start
      .CustomBuilder, "item")
    assertEqual(JSON.parse(swipeAction2)
      .$attrs
      .swipeAction
      .end
      .CustomBuilder, "item")
    let swipeAction3: string = await listItem3.getInspectorInfo()
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .builder
      .CustomBuilder, "item")
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .actionAreaDistance, '10px')
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .onAction, "NO")
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .onEnterActionArea, "NO")
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .onExitActionArea, "NO")
    assertEqual(JSON.parse(swipeAction3)
      .$attrs
      .swipeAction
      .end
      .onStateChange, "NO")
    await button.tap()
    let swipeAction4: string = await listItem3.getInspectorInfo()
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .builder
      .CustomBuilder, "item")
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .actionAreaDistance, $r('app.string.length'))
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .onAction, "OR")
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .onEnterActionArea, "OR")
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .onExitActionArea, "OR")
    assertEqual(JSON.parse(swipeAction4)
      .$attrs
      .swipeAction
      .end
      .onStateChange, "OR")
  }, 0)
}
