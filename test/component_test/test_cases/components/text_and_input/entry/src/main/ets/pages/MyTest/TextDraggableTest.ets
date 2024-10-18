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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function textDraggableTest() {
  /*
   * Text组件 Draggable属性
   * 找到画面id为textDraggable的Text组件
   * 找到画面文本为TextDraggable的Button组件
   * 获取text1的Draggable属性与期待值true比对
   * 点击button1，变更text1的Draggable属性值为false
   * 获取text1的Draggable属性与期待值false比对
   */
  defineTest('textDraggableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textDraggableTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('textDraggable1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextDraggable').enabled(true))

    let draggable1: string = await text.getInspectorInfo()
    assertFalse(JSON.parse(draggable1).$attrs.draggable == undefined)
    assertTrue(JSON.parse(draggable1).$attrs.draggable)

    await button.tap()
    let draggable2: string = await text.getInspectorInfo()
    assertFalse(JSON.parse(draggable2).$attrs.draggable)
  }, 0)
}