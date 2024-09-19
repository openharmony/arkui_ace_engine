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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function imageSpanVerticalAlignTest() {
  /*
   * ImageSpan组件 VerticalAlign属性
   * 找到画面id为imageSpanVerticalAlign1，imageSpanVerticalAlign2的ImageSpan组件
   * 找到画面文本为ImageSpanVerticalAlign1,ImageSpanVerticalAlign2的Button组件
   * 获取imageSpan1的VerticalAlign属性与期待值ImageSpanAlignment.TOP比对
   * 获取imageSpan2的VerticalAlign属性与期待值ImageSpanAlignment.BOTTOM比对
   * 点击button1，变更imageSpan2的VerticalAlign属性值为ImageSpanAlignment.CENTER
   * 获取imageSpan2的VerticalAlign属性与期待值ImageSpanAlignment.CENTER比对
   * 点击button2，变更imageSpan2的VerticalAlign属性值为ImageSpanAlignment.BASELINE
   * 获取imageSpan2的VerticalAlign属性与期待值ImageSpanAlignment.BASELINE比对
   */
  defineTest('imageSpanVerticalAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageSpanVerticalAlignTestDemo running")
    let driver: Tester = Tester.create()
    let imageSpan1: Component = await driver.findComponent(Matcher.create().id('imageSpanVerticalAlign1').enabled(true))
    let imageSpan2: Component = await driver.findComponent(Matcher.create().id('imageSpanVerticalAlign2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageSpanVerticalAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageSpanVerticalAlign2').enabled(true))

    let verticalAlign1: string = await imageSpan1.getInspectorInfo()
    assertEqual(JSON.parse(verticalAlign1).$attrs.verticalAlign, 'VerticalAlign.TOP')
    let verticalAlign2: string = await imageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(verticalAlign2).$attrs.verticalAlign, 'VerticalAlign.BOTTOM')

    await button1.tap()
    let verticalAlign3: string = await imageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(verticalAlign3).$attrs.verticalAlign, 'VerticalAlign.CENTER')
    await button2.tap()
    let verticalAlign4: string = await imageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(verticalAlign4).$attrs.verticalAlign, 'VerticalAlign.BASELINE')
  }, 0)
}