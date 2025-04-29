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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function heightTest() {
  /*
  * 使用 Column容器 Height属性
  * 找到画面id为columnHeight1，columnHeight2的Column组件
  * 找到画面文本为ButtonHeight的Button组件
  * 获取columnHeight1的Height属性与期待值'20.00vp'比对
  * 获取columnHeight2的Height属性与期待值'30.00px'比对
  * 点击button，变更columnHeight2的Height属性值为$r('app.string.common_height')
  * 获取columnHeight2的Height属性与期待值$r('app.string.common_height')比对
  */
  defineTest('heightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('heightTestDemo running')
    let driver: Tester = Tester.create()
    let columnHeight1: Component = await driver.findComponent(Matcher.create().id('columnHeight1').enabled(true))
    let columnHeight2: Component = await driver.findComponent(Matcher.create().id('columnHeight2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonHeight').enabled(true))
    let height1: string = await columnHeight1.getInspectorInfo()
    assertEqual(JSON.parse(height1).$attrs.height, '20.00vp')
    let height2: string = await columnHeight2.getInspectorInfo()
    assertEqual(JSON.parse(height2).$attrs.height, '30.00px')
    await button.tap()
    let height3: string = await columnHeight2.getInspectorInfo()
    assertEqual(JSON.parse(height3).$attrs.height, $r('app.string.common_height'))
  }, 0)
}