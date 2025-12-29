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
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { photoAccessHelper } from '@kit.MediaLibraryKit';
import { Constants } from '../common/CommonConstants';
import { FileUtils } from '../utils/FileUtils';


const tag: string = 'PhotoSelect';

@ComponentV2
export struct PhotoSelect {
  private static DEFAULT_COUNT: number = 4;
  @Param @Require imageInfoArr: Array<imageGeneration.ImageItem>;
  @Param @Require imageMatrixArr: number[][];
  @Event setImgCounts?: (count: number) => void;

  private getSelectPhotoLength(): number {
    let result = 0;
    for (let i = 0; i < this.imageInfoArr.length; i++) {
      if (!this.invalidImageInfo(i)) {
        result++;
      }
    }
    return result;
  }

  private openPhotoPicker(): void {
    if (this.getSelectPhotoLength() >= 4) {
      return;
    }
    let photoPicker = new photoAccessHelper.PhotoViewPicker();
    photoPicker.select({
      MIMEType: photoAccessHelper.PhotoViewMIMETypes.IMAGE_TYPE,
      isOriginalSupported: true,
      maxSelectNumber: PhotoSelect.DEFAULT_COUNT - this.getSelectPhotoLength(),
      combinedMediaTypeFilter: ['image|*|image/jpeg,image/png,image/heic,image/bmp,image/webp']
    }).then((result: photoAccessHelper.PhotoSelectResult) => {
      this.handleSelectedUri(result.photoUris);
    })
  }

  private deleteImageInfo(index: number): void {
    if (index < 0 || index > PhotoSelect.DEFAULT_COUNT) {
      console.log(tag, `invalid index: ${index}`);
      return;
    }
    this.imageInfoArr[index].url = Constants.NOT_SELECTED_NAME;
    this.imageInfoArr[index].image?.release();
    this.imageMatrixArr[index] = [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ];
    this.resortImageList();
  }

  private moveImageInfo(start: number, end: number): void {

    if (start === end) {
      return;
    }
    let zIndexArr: number[] = [];
    for (let i = 0; i < this.imageInfoArr.length; i++) {
      zIndexArr.push(this.imageInfoArr[start].zIndex ?? 0);
    }

    if (start > end) {
      let imageInfo = this.imageInfoArr[start];
      this.imageInfoArr.splice(start, 1);
      this.imageInfoArr.splice(end, 0, imageInfo);

      let matrixInfo = this.imageMatrixArr[start];
      this.imageMatrixArr.splice(start, 1);
      this.imageMatrixArr.splice(end, 0, matrixInfo);

    } else {
      let imageInfo = this.imageInfoArr[start];
      this.imageInfoArr.splice(start, 1);
      this.imageInfoArr.splice(end - 1, 0, imageInfo);

      let matrixInfo = this.imageMatrixArr[start];
      this.imageMatrixArr.splice(start, 1);
      this.imageMatrixArr.splice(end - 1, 0, matrixInfo);
    }
    this.resortImageList();
    for (let i = 0; i < zIndexArr.length; i++) {
      this.imageInfoArr[i].zIndex = zIndexArr[i];
    }
  }

  private resortImageList(): void {
    let images: imageGeneration.ImageItem[] = [];
    let matrixTmp: number[][] = [];
    for (let i = 0; i < this.imageInfoArr.length; i++) {
      if (!this.invalidImageInfo(i)) {
        images.push(this.imageInfoArr[i]);
        matrixTmp.push(this.imageMatrixArr[i])
      }
      this.imageInfoArr[i] = { image: undefined, url: Constants.NOT_SELECTED_NAME };
      this.imageMatrixArr[i] = [
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
      ];
    }
    for (let i = 0; i < images.length; i++) {
      this.imageInfoArr[i] = images[i];
      this.imageMatrixArr[i] = matrixTmp[i];
    }

    if (this.setImgCounts) {
      this.setImgCounts(images.length);
    }
  }

  private enablePhotoPicker(index: number): boolean {
    if (!this.invalidImageInfo(index)) {
      return false;
    }
    if (index === 0) {
      return true;
    }
    return !this.invalidImageInfo(index - 1);
  }

  private getMaxZIndex(): number {
    let maxZIndex: number = 0;
    for (let i = 0; i < this.imageInfoArr.length; i++) {
      if (!this.invalidImageInfo(i)) {
        maxZIndex = this.imageInfoArr[i].zIndex ?? 0;
      } else {
        return maxZIndex;
      }
    }
    return maxZIndex;
  }

  // only handle file://media//xxx
  private handleSelectedUri(selectedUris: string[]): void {
    for (let i = 0, j = 0; i < this.imageInfoArr.length && j < selectedUris.length; i++, j++) {
      if (!this.invalidImageInfo(i)) {
        j--;
        continue;
      }
      let imageInfo: imageGeneration.ImageItem | undefined = FileUtils.createPixelMap(selectedUris[j]);
      if (imageInfo === undefined) {
        i--;
        console.log(tag, 'parse selected uri error');
        return;
      }
      imageInfo.zIndex = this.getMaxZIndex() + 1;
      this.imageInfoArr[i] = imageInfo;
      if (this.setImgCounts) {
        this.setImgCounts(i + 1);
      }
    }
  }

  private invalidImageInfo(index: number): boolean {
    if (index < 0 || index > PhotoSelect.DEFAULT_COUNT) {
      console.log(tag, `invalid index: ${index}`);
      return true;
    }
    return this.imageInfoArr[index].url === Constants.NOT_SELECTED_NAME;
  }

  @Builder
  previewImageInfo(index: number) {
    if (!this.invalidImageInfo(index)) {
      Column() {
        Stack() {
          Image((this.imageInfoArr[index]).image)
            .syncLoad(true)
            .draggable(false)
            .borderRadius(12)
            .clip(true)
        }
        .alignContent(Alignment.Top)
        .width(56)
        .height(56)
        .borderRadius(12)
        .clip(true)
      }
    }
  }

  @Builder
  MyMagicCanvasSquaredBuilder(index: number) {
    if (this.invalidImageInfo(index)) {
      Stack() {
        Column()
          .backgroundColor($r('sys.color.comp_background_tertiary'))
          .height(56)
          .width(56)
          .borderRadius(12)
        if (this.enablePhotoPicker(index)) {
          SymbolGlyph($r('sys.symbol.plus'))
            .height(24)
            .width(24)
            .fontSize(24)
            .position({ x: 16, y: 16 })
            .draggable(false)
            .fontColor([$r('sys.color.icon_tertiary')])
        }
      }
      .onClick(() => {
        if (!this.enablePhotoPicker(index)) {
          return;
        }
        // Show picker
        this.openPhotoPicker();
      })
      .height(56)
      .width(56)
      .borderRadius(12)
      .clip(true)
    } else {
      Stack() {
        Column()
          .backgroundColor($r('sys.color.comp_background_tertiary'))
          .height(56)
          .width(56)
          .borderRadius(12)
        Image((this.imageInfoArr[index]).image)
          .borderRadius(12)
          .draggable(false)
          .syncLoad(true)
        Row() {
          Stack() {
            Column()
              .borderRadius('50%')
              .backgroundColor('#66000000')
              .width(16)
              .height(16)
              .margin(4)
            //Image($r('app.media.delect'))
            Image('xx')
              //.fillColor('#40808080')
              .fillColor(Color.White)
              .width(16)
              .height(16)
              .onClick(() => {
                this.deleteImageInfo(index);
              })
              .draggable(false)
              .margin(4)
              .borderRadius('50%')
              .responseRegion({
                x: -4,
                y: -4,
                width: 24,
                height: 24
              })
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.End)
        Row() {
          Text('图' + (index + 1))
            .fontColor('#FFFFFF')
            .fontWeight(FontWeight.Medium)
            .fontSize(12)
            .position({ x: 4, y: 36 })
            .width(48)
            .height(16)
            .textAlign(TextAlign.Center)
            .textShadow({
              offsetX: 0,
              offsetY: -2,
              radius: 8,
              color: '#66000000',
              type: ShadowType.COLOR
            })
        }
        .linearGradient({
          angle: 180,
          colors:[ ['#00000000', 0], ['#11000000', 0.5],  ['#66000000', 1]]
        })
        .height(56)
        .width(56)
        .hitTestBehavior(HitTestMode.Transparent)
      }
      .align(Alignment.Center)
      .alignContent(Alignment.Top)
      .height(56)
      .width(56)
      .borderRadius(12)
      .clip(true)
    }
  }

  build() {
    Column() {
      List() {
        ForEach(this.imageInfoArr, (item: imageGeneration.ImageItem, index: number) => {
          ListItem() {
            this.MyMagicCanvasSquaredBuilder(index)
          }
          .height(56)
          .width(56)
        }, (item: imageGeneration.ImageItem, index: number) => {
          return '' + index + (item?.url ?? 'imageGeneration') +  this.enablePhotoPicker(index);
        })
      }
      .onItemDragStart((event: ItemDragInfo, index: number) => {
        if (this.getSelectPhotoLength() <= 1) {
          return;
        }
        if (this.invalidImageInfo(index)) {
          return;
        }
        return this.previewImageInfo(index);
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        if (!isSuccess || insertIndex < 0 || insertIndex >= this.imageInfoArr.length) {
          return;
        }
        this.moveImageInfo(itemIndex, insertIndex);
      })
      .listDirection(Axis.Horizontal)
      .width('100%')
      .height('100%')
      .alignListItem(ListItemAlign.Center)
      .lanes(4, '12px')
    }
    .width(56)
    .height(260)
    .margin({ bottom: 6 })
    .justifyContent(FlexAlign.Center)
  }
}
