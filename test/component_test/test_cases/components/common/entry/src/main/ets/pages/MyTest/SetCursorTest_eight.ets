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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'
import pointer from '@ohos.multimodalInput.pointer';

export default async function setCursorTest_eight() {
  /*
  * Row组件 setCursor属性
  * 找到画面id为rowSetCursor29、rowSetCursor30的Row组件
  * 找到画面文本为ButtonSetCursor1的Button组件
  * 获取rowSetCursor29的setCursor属性与期待值pointer.PointerStyle.LOADING比对
  * 获取rowSetCursor2的setCursor属性与期待值pointer.PointerStyle.LOADING比对
  * 点击button1，变更rowSetCursor29的setCursor属性值为pointer.PointerStyle.RUNNING
  * 获取rowSetCursor29的ClickEffect属性与期待值pointer.PointerStyle.RUNNING比对
  */
  defineTest('setCursorTest_eightDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("setCursorTest_eightDemo running")
    let driver: Tester = Tester.create()
    let rowSetCursor29: Component = await driver.findComponent(Matcher.create().id('rowSetCursor29').enabled(true))
    let rowSetCursor30: Component = await driver.findComponent(Matcher.create().id('rowSetCursor30').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonSetCursor1').enabled(true))
    let setCursor1: string = await rowSetCursor29.getInspectorInfo()
    assertFalse(JSON.parse(setCursor1)
      .$attrs
      .setCursor == undefined)
    assertEqual(JSON.parse(setCursor1)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.LOADING)
    let setCursor2: string = await rowSetCursor30.getInspectorInfo()
    assertEqual(JSON.parse(setCursor2)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.LOADING)
    await button1.tap()
    let setCursor5: string = await rowSetCursor30.getInspectorInfo()
    assertEqual(JSON.parse(setCursor5).$attrs.clickEffect.value, pointer.PointerStyle.RUNNING)
  }, 0)
}