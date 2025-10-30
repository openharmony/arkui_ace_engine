/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


import { ComponentContent } from '@kit.ArkUI';

@Builder
export function SliderPrefixSuffixBuilder(name: string, param: Object) {
  SliderPrefixSuffixExample()
}

class NodeParams {
  public param: ResourceStr = '';

  constructor(param: ResourceStr) {
    this.param = param;
  }
}

@Builder
function textBuilder(params: NodeParams) {
  Text(params.param)
    .fontSize($r('sys.float.Caption_L'))
    .clip(true)
    .textAlign(TextAlign.Center)
    .fontColor(Color.Black)
}

@Entry
@Component
struct SliderPrefixSuffixExample {
  pathStack: NavPathStack = new NavPathStack()

  private preOutSet: string = 'OFF';
  private sufOutSet: string = 'MAX';
  private preIntSet: string = '低';
  private sufIntSet: string = '高';
  private uiContext: UIContext = this.getUIContext();

  private preOutSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preOutSet));
  private sufOutSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufOutSet));
  private preIntSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preIntSet));
  private sufIntSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufIntSet));


  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Text('outset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)
        Row() {
          Slider({
            value: 50,
            min: 0,
            max: 100,
            step:10,
            style: SliderStyle.OutSet
          })
            .borderRadius($r('sys.float.corner_radius_level8'))
            .backgroundColor(Color.White)
            .selectedColor('#ff7700ff')
            .trackBorderRadius($r('sys.float.corner_radius_level8'))
            .trackThickness(10)
            .selectedBorderRadius($r('sys.float.corner_radius_level7'))
            .stepSize(8)
            .stepColor($r('sys.color.comp_background_secondary'))
            .blockColor(Color.White)
            .height(40)
            .showSteps(true)
            .blockStyle({ type: SliderBlockType.DEFAULT })
            .showTips(true)
            .blockSize({
              width: 20,
              height: 20
            })
            .prefix(this.preOutSetNode, {
              accessibilityText: 'preOutSetNode',
              accessibilityDescription: 'preOutSetNodeDescription',
              accessibilityLevel: 'auto',
              accessibilityGroup: true
            })
            .suffix(this.sufOutSetNode, {
              accessibilityText: 'sufOutSetNode',
              accessibilityDescription: 'sufOutSetNodeDescription',
              accessibilityLevel: 'auto',
              accessibilityGroup: true
            })
        }
        .width('80%')

        Text('inset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)
        Row() {
          Slider({
            value: 50,
            min: 0,
            max: 100,
            step:10,
            style: SliderStyle.InSet
          })
            .borderRadius($r('sys.float.corner_radius_level7'))
            .backgroundColor($r('sys.color.comp_background_tertiary'))
            .trackBorderRadius($r('sys.float.corner_radius_level7'))
            .trackThickness(36)
            .selectedBorderRadius($r('sys.float.corner_radius_level7'))
            .stepSize(8)
            .stepColor($r('sys.color.comp_background_secondary'))
            .blockColor(Color.White)
            .width('85%')
            .height(40)
            .showSteps(true)
            .blockStyle({ type: SliderBlockType.DEFAULT })
            .showTips(true)
            .blockSize({
              width: 20,
              height: 20
            })
            .selectedColor(Color.White)
            .prefix(this.preIntSetNode, {
              accessibilityText: 'preIntSetNode',
              accessibilityDescription: 'preIntSetNodeDescription',
              accessibilityLevel: 'auto',
              accessibilityGroup: true
            })
            .suffix(this.sufIntSetNode, {
              accessibilityText: 'sufIntSetNode',
              accessibilityDescription: 'sufIntSetNodeDescription',
              accessibilityLevel: 'auto',
              accessibilityGroup: true
            })
        }
        .width('80%')
      }
    }
    .title('SliderPrefixSuffix')
    .onBackPressed(() => {
    this.pathStack.pop()
    return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { SliderPrefixSuffixExample };