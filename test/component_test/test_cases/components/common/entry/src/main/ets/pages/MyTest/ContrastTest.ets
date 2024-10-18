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

export default async function contrastTest() {
  /*
  * image组件contrast属性
  * 找到画面id为imageContrast1的image组件
  * 找到画面文本为ButtonContrast1的Button组件
  * 获取imageContrast1的contrast属性与期待值2比对
  * 点击button1，变更imageContrast1的contrast属性值为-1
  * 获取imageContrast1的contrast属性与期待值0比对
  */
  defineTest('contrastTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("contrastTestDemo running")
    let driver: Tester = Tester.create()
    let imageContrast1: Component = await driver.findComponent(Matcher.create().id('imageContrast1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonContrast1').enabled(true))
    let contrast1: string = await imageContrast1.getInspectorInfo()
    assertEqual(JSON.parse(contrast1).$attrs.contrast, 2)
    await button1.tap()
    let contrast2: string = await imageContrast1.getInspectorInfo()
    assertEqual(JSON.parse(contrast2).$attrs.contrast, 0)
  }, 0)
}