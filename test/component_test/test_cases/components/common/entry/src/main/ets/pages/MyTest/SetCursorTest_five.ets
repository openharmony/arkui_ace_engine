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

export default async function setCursorTest_five() {
  /*
  * Row组件 setCursor属性
  * 找到画面id为rowSetCursor17、rowSetCursor18、rowSetCursor19、rowSetCursor20的Row组件
  * 找到画面文本为ButtonSetCursor1、ButtonSetCursor2的Button组件
  * 获取rowSetCursor17的setCursor属性与期待值pointer.PointerStyle.SCREENSHOT_CHOOSE比对
  * 获取rowSetCursor18的setCursor属性与期待值pointer.PointerStyle.SCREENSHOT_CURSOR比对
  * 获取rowSetCursor19的setCursor属性与期待值pointer.PointerStyle.TEXT_CURSOR比对
  * 获取rowSetCursor20的setCursor属性与期待值pointer.PointerStyle.ZOOM_IN比对
  * 点击button1，变更rowSetCursor19的setCursor属性值为pointer.PointerStyle.ZOOM_OUT
  * 获取rowSetCursor19的ClickEffect属性与期待值pointer.PointerStyle.ZOOM_OUT比对
  * 点击button2，变更rowSetCursor20的setCursor属性值为pointer.PointerStyle.MIDDLE_BTN_EAST
  * 获取rowSetCursor20的ClickEffect属性与期待值pointer.PointerStyle.MIDDLE_BTN_EAST比对
  */
  defineTest('setCursorTest_fiveDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("setCursorTest_fiveDemo running")
    let driver: Tester = Tester.create()
    let row1: Component = await driver.findComponent(Matcher.create().id('rowSetCursor17').enabled(true))
    let row2: Component = await driver.findComponent(Matcher.create().id('rowSetCursor18').enabled(true))
    let row3: Component = await driver.findComponent(Matcher.create().id('rowSetCursor19').enabled(true))
    let row4: Component = await driver.findComponent(Matcher.create().id('rowSetCursor20').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonSetCursor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonSetCursor2').enabled(true))
    let setCursor1: string = await row1.getInspectorInfo()
    assertFalse(JSON.parse(setCursor1)
      .$attrs
      .onHover == undefined)
    assertEqual(JSON.parse(setCursor1)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.SCREENSHOT_CHOOSE)
    let setCursor2: string = await row2.getInspectorInfo()
    assertEqual(JSON.parse(setCursor2)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.SCREENSHOT_CURSOR)
    let setCursor3: string = await row3.getInspectorInfo()
    assertEqual(JSON.parse(setCursor3)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.TEXT_CURSOR)
    let setCursor4: string = await row4.getInspectorInfo()
    assertEqual(JSON.parse(setCursor4)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.ZOOM_IN)
    await button1.tap()
    let setCursor5: string = await row3.getInspectorInfo()
    assertEqual(JSON.parse(setCursor5).$attrs.clickEffect.value, pointer.PointerStyle.ZOOM_OUT)
    await button2.tap()
    let setCursor6: string = await row4.getInspectorInfo()
    assertEqual(JSON.parse(setCursor6).$attrs.clickEffect.value, pointer.PointerStyle.MIDDLE_BTN_EAST)
  }, 0)
}