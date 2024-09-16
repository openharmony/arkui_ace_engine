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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function pixelRoundTest() {
  /*
   * Row组件 PixelRound通用属性
   * 找到画面id为rowPixelRound的组件
   * 找到画面text为ButtonPixelRound的button组件
   * 获取rowPixelRound的PixelRound属性与期待值
   * {start: PixelRoundCalcPolicy.NO_FORCE_ROUND, top: PixelRoundCalcPolicy.NO_FORCE_ROUND,
   * end: PixelRoundCalcPolicy.NO_FORCE_ROUND, bottom: PixelRoundCalcPolicy.NO_FORCE_ROUND } 比较
   * 点击button，变更rowPixelRound的PixelRound属性为
   * {start: PixelRoundCalcPolicy.FORCE_CEIL, top: PixelRoundCalcPolicy.FORCE_CEIL,
   * end: PixelRoundCalcPolicy.FORCE_CEIL, bottom: PixelRoundCalcPolicy.FORCE_CEIL }
   * 获取rowPixelRound的pixelRound属性中的start与期待值
   * {start: PixelRoundCalcPolicy.FORCE_CEIL, top: PixelRoundCalcPolicy.FORCE_CEIL,
   * end: PixelRoundCalcPolicy.FORCE_CEIL, bottom: PixelRoundCalcPolicy.FORCE_CEIL } 比较
   * 点击button，变更rowPixelRound的pixelRound属性为
   * {start: PixelRoundCalcPolicy.FORCE_FLOOR, top: PixelRoundCalcPolicy.FORCE_FLOOR,
   * end: PixelRoundCalcPolicy.FORCE_FLOOR, bottom: PixelRoundCalcPolicy.FORCE_FLOOR }
   * 获取rowPixelRound的pixelRound属性与期待值
   * {start: PixelRoundCalcPolicy.FORCE_FLOOR, top: PixelRoundCalcPolicy.FORCE_FLOOR,
   * end: PixelRoundCalcPolicy.FORCE_FLOOR, bottom: PixelRoundCalcPolicy.FORCE_FLOOR } 比较
   */
  defineTest('pixelRoundTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('pixelRoundTestDemo running')
    let driver: Tester = Tester.create()
    let rowPixelRound: Component = await driver.findComponent(Matcher.create().id('rowPixelRound').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonPixelRound').enabled(true))

    let pixelRound1: string = await rowPixelRound.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(pixelRound1).$attrs.pixelRound).start, 'PixelRoundCalcPolicy.NO_FORCE_ROUND')
    assertEqual(JSON.parse(JSON.parse(pixelRound1).$attrs.pixelRound).top, 'PixelRoundCalcPolicy.NO_FORCE_ROUND')
    assertEqual(JSON.parse(JSON.parse(pixelRound1).$attrs.pixelRound).end, 'PixelRoundCalcPolicy.NO_FORCE_ROUND')
    assertEqual(JSON.parse(JSON.parse(pixelRound1).$attrs.pixelRound).bottom, 'PixelRoundCalcPolicy.NO_FORCE_ROUND')

    await button.tap()
    let pixelRound2: string = await rowPixelRound.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(pixelRound2).$attrs.pixelRound).start, 'PixelRoundCalcPolicy.FORCE_CEIL')
    assertEqual(JSON.parse(JSON.parse(pixelRound2).$attrs.pixelRound).top, 'PixelRoundCalcPolicy.FORCE_CEIL')
    assertEqual(JSON.parse(JSON.parse(pixelRound2).$attrs.pixelRound).end, 'PixelRoundCalcPolicy.FORCE_CEIL')
    assertEqual(JSON.parse(JSON.parse(pixelRound2).$attrs.pixelRound).bottom, 'PixelRoundCalcPolicy.FORCE_CEIL')

    await button.tap()
    let pixelRound3: string = await rowPixelRound.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(pixelRound3).$attrs.pixelRound).start, 'PixelRoundCalcPolicy.FORCE_FLOOR')
    assertEqual(JSON.parse(JSON.parse(pixelRound3).$attrs.pixelRound).top, 'PixelRoundCalcPolicy.FORCE_FLOOR')
    assertEqual(JSON.parse(JSON.parse(pixelRound3).$attrs.pixelRound).end, 'PixelRoundCalcPolicy.FORCE_FLOOR')
    assertEqual(JSON.parse(JSON.parse(pixelRound3).$attrs.pixelRound).bottom, 'PixelRoundCalcPolicy.FORCE_FLOOR')
  }, 0)
}