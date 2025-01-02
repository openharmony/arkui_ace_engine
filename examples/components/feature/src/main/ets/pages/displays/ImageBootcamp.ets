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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled, SliderBlock, IconBlock, ColorBlock } from 'common';

@Component
export struct ImageboxGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFocusable: boolean = true;
  @State compFocusable: boolean = true;
  @State enableCustomSize: boolean = true;
  @State customSize: string = '64*64';
  @State enableBorderRadius: boolean = false;
  @State imageBorderRadius: number = 0;
  @State enableMargin: boolean = true;
  @State compMargin: number = 0;
  @State enableImage: boolean = true;
  @State image: ResourceStr = $r('app.media.startIcon');
  @State enableObjectFit: boolean = false;
  @State objectFit: ImageFit = ImageFit.Cover;
  @State enableObjectRepeat: boolean = false;
  @State objectRepeat: ImageRepeat = ImageRepeat.NoRepeat
  @State enableInterpolation: boolean = false;
  @State interpolation: ImageInterpolation = ImageInterpolation.Low
  @State enableRenderMode: boolean = false;
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State enableImageSourceSizeWidth: boolean = false;
  @State imageSourceSizeWidth: number | undefined = undefined;
  @State enableImageSourceSizeHeight: boolean = false;
  @State imageSourceSizeHeight: number | undefined = undefined;
  @State enableMatchTextDirection: boolean = false;
  @State matchTextDirection: boolean = false;
  @State enableFitOriginalSize: boolean = false;
  @State fitOriginalSize: boolean = false;
  @State enableFillColor: boolean = false;
  @State fillColor: ResourceColor | undefined = undefined;
  @State enableAutoResize: boolean = false;
  @State autoResize: boolean = false;
  @State enableSyncLoad: boolean = false;
  @State syncLoad: boolean = false;
  @State enableCopyOption: boolean = false;
  @State copyOption: CopyOptions = CopyOptions.None
  @State enableEnableColorFilter: boolean = false;
  @State enableColorFilter: boolean = false;
  private colorFilterMatrix: number[] = [1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0];
  @State colorFilter: ColorFilter | undefined = undefined
  @State enableDraggable: boolean = false;
  @State eDraggable: boolean = false;
  @State enableEnableAnalyzer: boolean = false;
  @State enableAnalyzer: boolean = false;
  @State enableResizableSliceTop: boolean = false;
  @State resizableSliceTop: number = 0;
  @State enableResizableSliceRight: boolean = false;
  @State resizableSliceRight: number = 0;
  @State enableResizableSliceBottom: boolean = false;
  @State resizableSliceBottom: number = 0;
  @State enableResizableSliceLeft: boolean = false;
  @State resizableSliceLeft: number = 0;
  @State enablePrivacySensitive: boolean = false;
  @State privacySensitive: boolean = false;
  @State enableDynamicRangeMode: boolean = false;
  @State dynamicRangeMode: DynamicRangeMode = DynamicRangeMode.STANDARD
  @State enableDragGray: boolean = false;
  @State dragGray: DragPreviewMode = DragPreviewMode.AUTO;



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
      Row({space:20}) {
        Column(){
          Image(useEnabled(this.enableImage, this.image))
            .width(useEnabled(this.enableCustomSize, this.customSize.split('*')[0]))
            .height(useEnabled(this.enableCustomSize, this.customSize.split('*')[1]))
            .focusable(useEnabled(this.enableFocusable, this.compFocusable))
            .borderRadius(useEnabled(this.enableBorderRadius, this.imageBorderRadius))
            .margin(useEnabled(this.enableMargin, this.compMargin))
            .objectFit(useEnabled(this.enableObjectFit,this.objectFit))
            .objectRepeat(useEnabled(this.enableObjectRepeat,this.objectRepeat))
            .interpolation(useEnabled(this.enableInterpolation,this.interpolation))
            .renderMode(useEnabled(this.enableRenderMode,this.renderMode))
            .sourceSize({
              width: useEnabled(this.enableImageSourceSizeWidth, this.imageSourceSizeWidth),
              height: useEnabled(this.enableImageSourceSizeHeight, this.imageSourceSizeHeight)
            })
            .matchTextDirection(useEnabled(this.enableMatchTextDirection,this.matchTextDirection))
            .fitOriginalSize(useEnabled(this.enableFitOriginalSize,this.fitOriginalSize))
            .fillColor(useEnabled(this.enableFillColor,this.fillColor))
            .autoResize(useEnabled(this.enableAutoResize,this.autoResize))
            .syncLoad(useEnabled(this.enableSyncLoad,this.syncLoad))
            .copyOption(useEnabled(this.enableCopyOption,this.copyOption))
            .draggable(useEnabled(this.enableDraggable,this.eDraggable))
            .enableAnalyzer(useEnabled(this.enableEnableAnalyzer,this.enableAnalyzer))
            .resizable({
              slice: {
                top: useEnabled(this.enableResizableSliceTop, this.resizableSliceTop),
                right: useEnabled(this.enableResizableSliceRight, this.resizableSliceRight),
                bottom: useEnabled(this.enableResizableSliceBottom, this.resizableSliceBottom),
                left: useEnabled(this.enableResizableSliceLeft, this.resizableSliceLeft)
              }
            })
            .privacySensitive(useEnabled(this.enablePrivacySensitive,this.privacySensitive))
            .dynamicRangeMode(useEnabled(this.enableDynamicRangeMode,this.dynamicRangeMode))
            .onDragStart(() => {})
            .dragPreviewOptions({ mode: useEnabled(this.enableDragGray, this.dragGray)})
        }
        if(this.enableColorFilter){
          Column(){
            Text('colorFilter.example')
            Image(useEnabled(this.enableImage, this.image))

              .colorFilter(this.colorFilter)
              .onClick(()=>{
                this.colorFilter = new ColorFilter(this.colorFilterMatrix);  ///
              })
          }
        }

      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        IconBlock({
          title: 'image',
          isEnabled: this.enableImage,
          icon: this.image,
        })

        RadioBlock({
          title: 'focusable',
          isEnabled: this.enableFocusable,
          value: this.compFocusable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'customSize',
          isEnabled: $enableCustomSize,
          value: $customSize,
          dataSource: [
            { label: '64x64', value: '64*64' },
            { label: '28x28', value: '28*28' },
            { label: '110x110', value: '110*110' }
          ]
        })

        SliderBlock({
          title: 'imageBorderRadius(vp)',
          isEnabled: $enableBorderRadius,
          value: $imageBorderRadius,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableMargin,
          value: $compMargin,
          min: 0,
          max: 20
        })


        RadioBlock({
          title: 'objectFit',
          isEnabled: this.enableObjectFit,
          value: this.objectFit,
          dataSource: [
            { label: 'Contain', value: ImageFit.Contain },
            { label: 'Cover', value: ImageFit.Cover },
            { label: 'Auto', value: ImageFit.Auto },
            { label: 'Fill', value: ImageFit.Fill },
            { label: 'ScaleDown', value: ImageFit.ScaleDown },
            { label: 'None', value: ImageFit.None },
            { label: 'TOP_START', value: ImageFit.TOP_START},
            { label: 'TOP', value: ImageFit.TOP },
            { label: 'TOP_END', value: ImageFit.TOP_END },
            { label: 'START', value: ImageFit.START },
            { label: 'CENTER', value: ImageFit.CENTER },
            { label: 'END', value: ImageFit.END },
            { label: 'BOTTOM_START', value: ImageFit.BOTTOM_START },
            { label: 'BOTTOM', value: ImageFit.BOTTOM },
            { label: 'BOTTOM_END', value: ImageFit.BOTTOM_END },
          ]
        })

        RadioBlock({
          title: 'objectRepeat',
          isEnabled: this.enableObjectRepeat,
          value: this.objectRepeat,
          dataSource: [
            { label: 'NoRepeat', value: ImageRepeat.NoRepeat },
            { label: 'X', value: ImageRepeat.X },
            { label: 'Y', value: ImageRepeat.Y },
            { label: 'XY', value: ImageRepeat.XY }
          ]
        })

        RadioBlock({
          title: 'interpolation',
          isEnabled: this.enableInterpolation,
          value: this.interpolation,
          dataSource: [
            { label: 'None', value: ImageInterpolation.None },
            { label: 'Low', value: ImageInterpolation.Low },
            { label: 'Medium', value: ImageInterpolation.Medium },
            { label: 'High', value: ImageInterpolation.High },
          ]
        })

        RadioBlock({
          title: 'renderMode',
          isEnabled: this.enableRenderMode,
          value: this.renderMode,
          dataSource: [
            { label: 'Original', value: ImageRenderMode.Original },
            { label: 'Template', value: ImageRenderMode.Template }
          ]
        })

        SliderBlock({
          title: 'imageSourceSize.width',
          isEnabled: this.enableImageSourceSizeWidth,
          value: this.imageSourceSizeWidth,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'imageSourceSize.height',
          isEnabled: this.enableImageSourceSizeHeight,
          value: this.imageSourceSizeHeight,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'matchTextDirection',
          isEnabled: this.enableMatchTextDirection,
          value: this.matchTextDirection,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'fitOriginalSize',
          isEnabled: this.enableFitOriginalSize,
          value: this.fitOriginalSize,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'fillColor',
          isEnabled: this.enableFillColor,
          color: this.fillColor
        })

        RadioBlock({
          title: 'autoResize',
          isEnabled: this.enableAutoResize,
          value: this.autoResize,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'syncLoad',
          isEnabled: this.enableSyncLoad,
          value: this.syncLoad,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'copyOption',
          isEnabled: this.enableCopyOption,
          value: this.copyOption,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        RadioBlock({
          title: 'colorFilter',
          isEnabled: this.enableEnableColorFilter,
          value: this.enableColorFilter,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'draggable',
          isEnabled: this.enableDraggable,
          value: this.eDraggable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'enableAnalyzer',
          isEnabled: this.enableEnableAnalyzer,
          value: this.enableAnalyzer,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'resizable.slice.top',
          isEnabled: this.enableResizableSliceTop,
          value: this.resizableSliceTop,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'resizable.slice.right',
          isEnabled: this.enableResizableSliceRight,
          value: this.resizableSliceRight,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'resizable.slice.bottom',
          isEnabled: this.enableResizableSliceBottom,
          value: this.resizableSliceBottom,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'resizable.slice.left',
          isEnabled: this.enableResizableSliceLeft,
          value: this.resizableSliceLeft,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'privacySensitive',
          isEnabled: this.enablePrivacySensitive,
          value: this.privacySensitive,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'dynamicRangeMode',
          isEnabled: this.enableDynamicRangeMode,
          value: this.dynamicRangeMode,
          dataSource: [
            { label: 'HIGH', value: DynamicRangeMode.HIGH },
            { label: 'CONSTRAINT', value: DynamicRangeMode.CONSTRAINT },
            { label: 'STANDARD', value: DynamicRangeMode.STANDARD }
          ]
        })

        RadioBlock({
          title: '拖拽背板图样式',
          isEnabled: $enableDragGray,
          value: $dragGray,
          dataSource: [
            { label: '默认', value: DragPreviewMode.AUTO },
            { label: '灰显', value: DragPreviewMode.ENABLE_DRAG_ITEM_GRAY_EFFECT }
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct ImageBootcampPreviewer {
  build() {
    ImageboxGroupBootcamp({
      title: '图片/Image'
    })
  }
}