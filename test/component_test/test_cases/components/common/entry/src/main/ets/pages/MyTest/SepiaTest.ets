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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function sepiaTest() {
  /*
  * button组件 sepia属性
  * 找到画面id为button1，的Button组件
  * 找到画面文本为 ButtonSepia2 的Button组件
  * 获取button1的sepia属性与期待值1比对
  * 点击button2，button1的sepia属性的值为0
  * 获取button1的sepia属性与期待值0比对
  */
  defineTest('sepiaTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("sepiaTestDemo running")
    let driver: Tester = Tester.create()
    let buttonSepia1: Component = await driver.findComponent(Matcher.create().id('buttonSepia1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonSepia2').enabled(true))
    let sepia1: string = await buttonSepia1.getInspectorInfo()
    assertEqual(JSON.parse(sepia1).$attrs.sepia, 1)
    await button2.tap()
    let sepia2: string = await buttonSepia1.getInspectorInfo()
    assertEqual(JSON.parse(sepia2).$attrs.sepia, 0)
  }, 0)
}