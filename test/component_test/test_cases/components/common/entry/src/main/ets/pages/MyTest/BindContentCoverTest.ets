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

export default async function bindContentCoverTest() {
  /*
   * bindContentCover 属性
   * 获取 id为 buttonBindContentCover6 的 Button 组件
   * 获取 文本 为 BindContent6 的 Button 组件
   * 获取 文本包括 'BindContent3' 的 Builder
   * 将 Builder 与 'myBuilder' 对比
   * 获取 buttonBindContentCover6 的值
   * 将 bindContentCover.isShow 与 false 对比
   * 将 bindContentCover.options.modalTransition 与  ModalTransition.NONE  对比
   * 将 bindContentCover.options.backgroundColor 与 Color.Orange 对比
   * 点击button6切换进builder界面
   * 获取组件id为 buttonBindContentCover3 buttonBindContentCover4 的两个 Button
   * 获取 buttonBindContentCover3 buttonBindContentCover4 buttonBindContentCover6 的值
   * buttonBindContentCover3 的 options.modalTransition 与 ModalTransition.DEFAULT 对比
   * buttonBindContentCover3 的 options.backgroundColor 与 Color.Pink 对比
   * buttonBindContentCover4 的 options.modalTransition 与 ModalTransition.ALPHA 对比
   * buttonBindContentCover4 的 options.backgroundColor 与 Color.Blue 对比
   * buttonBindContentCover7 的 bindContentCover.isShow 与 true 对比 
   * */
  defineTest('bindContentCoverTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindContentCoverTestDemo running')
    let driver: Tester = Tester.create()
    let buttonBindContentCover6: Component =
      await driver.findComponent(Matcher.create().id('buttonBindContentCover6').enabled(true))
    let bindContentCover6: string = await buttonBindContentCover6.getInspectorInfo()
    assertFalse(JSON.parse(bindContentCover6).$attrs.bindContentCover == undefined)
    assertFalse(JSON.parse(bindContentCover6).$attrs.bindContentCover.isShow)
    assertEqual(JSON.parse(bindContentCover6)
      .$attrs
      .bindContentCover
      .options
      .modalTransition, ModalTransition.NONE)
    assertEqual(JSON.parse(bindContentCover6)
      .$attrs
      .bindContentCover
      .options
      .backgroundColor, Color.Orange)
    await buttonBindContentCover6.tap()
    let myBuilder: Component = await driver.findComponent(Matcher.create().text('BindContent3').enabled(true))
    let bindContentCoverBuilder: string = await myBuilder.getType()
    assertEqual(bindContentCoverBuilder, 'myBuilder')
    let buttonBindContentCover3: Component =
      await driver.findComponent(Matcher.create().id('buttonBindContentCover3').enabled(true))
    let buttonBindContentCover4: Component =
      await driver.findComponent(Matcher.create().id('buttonBindContentCover4').enabled(true))
    let bindContentCover3: string = await buttonBindContentCover3.getInspectorInfo()
    let bindContentCover4: string = await buttonBindContentCover4.getInspectorInfo()
    let bindContentCover7: string = await buttonBindContentCover6.getInspectorInfo()
    assertEqual(JSON.parse(bindContentCover3)
      .$attrs
      .bindContentCover
      .options
      .modalTransition, ModalTransition.DEFAULT)
    assertEqual(JSON.parse(bindContentCover3)
      .$attrs
      .bindContentCover
      .options
      .backgroundColor, Color.Pink)
    assertEqual(JSON.parse(bindContentCover4)
      .$attrs
      .bindContentCover
      .options
      .modalTransition, ModalTransition.ALPHA)
    assertEqual(JSON.parse(bindContentCover4)
      .$attrs
      .bindContentCover
      .options
      .backgroundColor, Color.Blue)
    assertTrue(JSON.parse(bindContentCover7).$attrs.bindContentCover.isShow)
  }, 0)
}
