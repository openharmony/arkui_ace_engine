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
import { ColorBlock, Drawer, RadioBlock, SliderBlock, useEnabled} from 'common';

@Component
export struct DataPanelBootcamp{
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableCloseEffect: boolean = false;
  @State enableTrackBackgroundColor: boolean = false;
  @State enableStrokeWidth: boolean = false;
  @State enableValueColors: boolean = false;
  @State enableDataPanelShadowOptionsMultiShadowOptionsRadius: boolean = false;
  @State enableDataPanelShadowOptionsMultiShadowOptionsOffsetX: boolean = false;
  @State enableDataPanelShadowOptionsMultiShadowOptionsOffsetY: boolean = false;
  @State enableTrackShadowColors: boolean = false;
  @State closeEffectDataPane: boolean = false;
  @State trackBackgroundColorDataPane: string = '#08182431';
  @State strokeWidthDataPane: number = 24;
  @State dataPanelShadowOptionsMultiShadowOptionsRadius: number = 20;
  @State dataPanelShadowOptionsMultiShadowOptionsOffsetX: number = 5;
  @State dataPanelShadowOptionsMultiShadowOptionsOffsetY: number = 5;
  public color1: LinearGradient = new LinearGradient(
    [{ color: '#65EEC9A3', offset: 0 }, { color: '#FFEF629F', offset: 1 }]);
  public color2: LinearGradient = new LinearGradient(
    [{ color: '#FF67F9D4', offset: 0 }, { color: '#FFFF9554', offset: 1 }]);
  @State color3: string = '#00FF00';
  @State color4: string = '#20FF0000';
  public colorShadow1: LinearGradient = new LinearGradient(
    [{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }]);
  public colorShadow2: LinearGradient = new LinearGradient(
    [{ color: '#65e26709', offset: 0 }, { color: '#65efbd08', offset: 1 }]);
  public colorShadow3: LinearGradient = new LinearGradient(
    [{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 1 }]);
  public colorShadow4: LinearGradient = new LinearGradient(
    [{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }]);
  @State valueColorsDataPane: Array<LinearGradient | ResourceColor> = [
    this.color1, this.color2, this.color3, this.color4];
  @State trackShadowColorsDataPane: Array<LinearGradient | ResourceColor> = [
    this.colorShadow1, this.colorShadow2, this.colorShadow3, this.colorShadow4];

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Row(){
        Stack() {
          DataPanel({ values: [40, 25, 10, 5], max: 100, type: DataPanelType.Circle })
            .width(168).height(168)
            .closeEffect(useEnabled(this.enableCloseEffect,this.closeEffectDataPane))
            .trackBackgroundColor(useEnabled(this.enableTrackBackgroundColor,
              this.trackBackgroundColorDataPane))
            .strokeWidth(useEnabled(this.enableStrokeWidth,this.strokeWidthDataPane))
            .valueColors(useEnabled(this.enableValueColors,this.valueColorsDataPane))
            .trackShadow({
              radius: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsRadius,
                this.dataPanelShadowOptionsMultiShadowOptionsRadius),
              colors: useEnabled(this.enableTrackShadowColors,this.trackShadowColorsDataPane),
              offsetX: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsOffsetX,
                this.dataPanelShadowOptionsMultiShadowOptionsOffsetX),
              offsetY: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsOffsetY,
                this.dataPanelShadowOptionsMultiShadowOptionsOffsetY)
            })

          Column() {
            Text('75')
              .fontSize(35)
              .fontColor('#182431')
            Text('已使用98GB/128GB')
              .fontSize(8.17)
              .lineHeight(11.08)
              .fontWeight(500)
              .opacity(0.6)
          }
          Text('%')
            .fontSize(9.33)
            .lineHeight(12.83)
            .fontWeight(500)
            .opacity(0.6)
            .position({ x: 104.42, y: 78.17 })
        }

        DataPanel({ values: [20, 20, 20, 20], max: 100, type: DataPanelType.Circle }).width(214).height(214)
          .closeEffect(useEnabled(this.enableCloseEffect,this.closeEffectDataPane))
          .trackBackgroundColor(useEnabled(this.enableTrackBackgroundColor,this.trackBackgroundColorDataPane))
          .strokeWidth(useEnabled(this.enableStrokeWidth,this.strokeWidthDataPane))
          .valueColors(useEnabled(this.enableValueColors,this.valueColorsDataPane))
          .trackShadow({
            radius: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsRadius,
              this.dataPanelShadowOptionsMultiShadowOptionsRadius),
            colors: useEnabled(this.enableTrackShadowColors,this.trackShadowColorsDataPane),
            offsetX: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsOffsetX,
              this.dataPanelShadowOptionsMultiShadowOptionsOffsetX),
            offsetY: useEnabled(this.enableDataPanelShadowOptionsMultiShadowOptionsOffsetY,
              this.dataPanelShadowOptionsMultiShadowOptionsOffsetY)
          })
      }.margin({ bottom: 40 })
      .width('100%')
      Stack() {
        DataPanel({ values: [10, 10, 10, 10, 10, 10, 10, 10,10], max: 100, type: DataPanelType.Line })
          .width(300).height(20)
          .closeEffect(useEnabled(this.enableCloseEffect,this.closeEffectDataPane))
          .trackBackgroundColor(useEnabled(this.enableTrackBackgroundColor,this.trackBackgroundColorDataPane))
      }
    }
    .width('100%')
  }
  @Builder
  Parameters() {
    Scroll(){
      Column({ space: 8 }) {
        RadioBlock({
          title: 'closeEffect',
          isEnabled: $enableCloseEffect,
          value: $closeEffectDataPane,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        ColorBlock({
          title: 'trackBackgroundColor',
          isEnabled: $enableTrackBackgroundColor,
          color: $trackBackgroundColorDataPane
        })
        SliderBlock({
          title: 'strokeWidth',
          isEnabled: $enableStrokeWidth,
          value: $strokeWidthDataPane,
          min: 0,
          max: 40
        })
        ColorBlock({
          title: 'valueColors',
          isEnabled: $enableValueColors,
          color: $valueColorsDataPane,
        })
        SliderBlock({
          title: 'dataPanelShadowOptions.MultiShadowOptions.Radius',
          isEnabled: $enableDataPanelShadowOptionsMultiShadowOptionsRadius,
          value: $dataPanelShadowOptionsMultiShadowOptionsRadius,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'dataPanelShadowOptions.MultiShadowOptions.OffsetX',
          isEnabled: $enableDataPanelShadowOptionsMultiShadowOptionsOffsetX,
          value: $dataPanelShadowOptionsMultiShadowOptionsOffsetX,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'dataPanelShadowOptions.MultiShadowOptions.OffsetY',
          isEnabled: $enableDataPanelShadowOptionsMultiShadowOptionsOffsetY,
          value: $dataPanelShadowOptionsMultiShadowOptionsOffsetY,
          min: 0,
          max: 100
        })
        ColorBlock({
          title: 'colors',
          isEnabled: $enableTrackShadowColors,
          color: $trackShadowColorsDataPane
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct DataPanelBootcampPreviewer{
  build() {
    DataPanelBootcamp({
      title: '数据面板/DataPanel'
    })
  }
}