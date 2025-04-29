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

export default async function saturateTest() {
  /*
  * image组件 saturate属性
  * 找到画面id为 imageSaturate1 的image组件
  * 找到画面文本为 ButtonSaturate 的Button组件
  * 获取 imageSaturate1 的saturate属性与期待值20比对
  * 点击button1，变更 imageSaturate1 的saturate属性值为-1
  * 获取 imageSaturate1 的saturate属性与期待值0比对
  */
  defineTest('saturateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("saturateTestDemo running")
    let driver: Tester = Tester.create()
    let imageSaturate1: Component = await driver.findComponent(Matcher.create().id('imageSaturate1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonSaturate').enabled(true))
    let saturate1: string = await imageSaturate1.getInspectorInfo()
    assertEqual(JSON.parse(saturate1).$attrs.saturate, 20)
    await button1.tap()
    let saturate2: string = await imageSaturate1.getInspectorInfo()
    assertEqual(JSON.parse(saturate2).$attrs.saturate, 0)
  }, 0)
}