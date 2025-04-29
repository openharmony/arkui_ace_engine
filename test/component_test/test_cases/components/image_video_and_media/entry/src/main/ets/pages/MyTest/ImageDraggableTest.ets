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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function imageDraggableTest() {
  /*
* Image组件 Draggable属性
* 找到画面id为image的imageDraggable组件
* 找到画面文本为ImageDraggable1的Button组件
* 获取image的Draggable属性与期待值true比对
* 点击button，变更image的Draggable属性值为false
* 获取image的Draggable属性与期待值false比对
*/
  defineTest('imageDraggableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageDraggableTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageDraggable').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ImageDraggable1').enabled(true))
    let draggable1: string = await image.getInspectorInfo()
    assertTrue(JSON.parse(draggable1).$attrs.draggable)
    await button.tap()
    let draggable2: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(draggable2).$attrs.draggable)
  }, 0)
}