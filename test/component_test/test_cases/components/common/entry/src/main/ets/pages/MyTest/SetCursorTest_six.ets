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

export default async function setCursorTest_six() {
  /*
  * Row组件 setCursor属性
  * 找到画面id为rowSetCursor21、rowSetCursor22、rowSetCursor23、rowSetCursor24的Row组件
  * 找到画面文本为ButtonSetCursor1、ButtonSetCursor2的Button组件
  * 获取rowSetCursor21的setCursor属性与期待值pointer.PointerStyle.MIDDLE_BTN_WEST比对
  * 获取rowSetCursor22的setCursor属性与期待值pointer.PointerStyle.MIDDLE_BTN_SOUTH比对
  * 获取rowSetCursor23的setCursor属性与期待值pointer.PointerStyle.MIDDLE_BTN_NORTH比对
  * 获取rowSetCursor24的setCursor属性与期待值pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH比对
  * 点击button1，变更rowSetCursor23的setCursor属性值为pointer.MIDDLE_BTN_NORTH_EAST
  * 获取rowSetCursor23的ClickEffect属性与期待值pointer.PointerStyle.MIDDLE_BTN_NORTH_EAST比对
  * 点击button2，变更rowSetCursor24的setCursor属性值为pointer.PointerStyle.MIDDLE_BTN_NORTH_WEST
  * 获取rowSetCursor24的ClickEffect属性与期待值pointer.PointerStyle.MIDDLE_BTN_NORTH_WEST比对
  */
  defineTest('setCursorTest_sixDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("setCursorTest_sixDemo running")
    let driver: Tester = Tester.create()
    let row1: Component = await driver.findComponent(Matcher.create().id('rowSetCursor21').enabled(true))
    let row2: Component = await driver.findComponent(Matcher.create().id('rowSetCursor22').enabled(true))
    let row3: Component = await driver.findComponent(Matcher.create().id('rowSetCursor23').enabled(true))
    let row4: Component = await driver.findComponent(Matcher.create().id('rowSetCursor24').enabled(true))
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
      .value, pointer.PointerStyle.MIDDLE_BTN_WEST)
    let setCursor2: string = await row2.getInspectorInfo()
    assertEqual(JSON.parse(setCursor2)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.MIDDLE_BTN_SOUTH)
    let setCursor3: string = await row3.getInspectorInfo()
    assertEqual(JSON.parse(setCursor3)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.MIDDLE_BTN_NORTH)
    let setCursor4: string = await row4.getInspectorInfo()
    assertEqual(JSON.parse(setCursor4)
      .$attrs
      .onHover
      .setCursor
      .value, pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH)
    await button1.tap()
    let setCursor5: string = await row3.getInspectorInfo()
    assertEqual(JSON.parse(setCursor5).$attrs.clickEffect.value, pointer.PointerStyle.MIDDLE_BTN_NORTH_EAST)
    await button2.tap()
    let setCursor6: string = await row4.getInspectorInfo()
    assertEqual(JSON.parse(setCursor6).$attrs.clickEffect.value, pointer.PointerStyle.MIDDLE_BTN_NORTH_WEST)
  }, 0)
}