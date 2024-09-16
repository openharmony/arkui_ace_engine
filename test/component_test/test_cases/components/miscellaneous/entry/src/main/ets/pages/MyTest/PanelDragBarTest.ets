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
} from '@ohos.arkui.componentTest'

export default async function panelDragBarTest() {
  /*
   * Panel组件 DragBar属性
   * 找到画面id为panelDragBar的Panel组件
   * 找到画面文本为PanelDragBar的Button组件
   * 获取panel的DragBar属性与期待值true比对
   * 点击button，变更panel1的DragBar属性值为false
   * 获取panel的DragBar属性与期待值false比对
   */
  defineTest('panelDragBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelDragBarTestDemo running')

    let driver: Tester = Tester.create()
    let panel: Component = await driver.findComponent(Matcher.create().id('panelDragBar').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PanelDragBar').enabled(true))

    let dragBar1: string = await panel.getInspectorInfo()
    assertTrue(JSON.parse(dragBar1).$attrs.dragBar)

    await button.tap()
    let dragBar2: string = await panel.getInspectorInfo()
    assertFalse(JSON.parse(dragBar2).$attrs.dragBar)
  }, 0)
}