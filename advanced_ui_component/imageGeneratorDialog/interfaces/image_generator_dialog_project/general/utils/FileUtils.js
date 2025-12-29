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

import image from "@ohos.multimedia.image";
import fileUri from "@ohos.file.fileuri";
import fs from "@ohos.file.fs";
import { Constants } from '../common/CommonConstants';
export class FileUtils {
    static copyFileToDestination(sourceUri, destination) {
        try {
            let buf = new ArrayBuffer(Constants.FILE_BUFFER_SIZE);
            let readSize = 0;
            let file = fs.openSync(sourceUri, fs.OpenMode.READ_ONLY);
            let readLen = fs.readSync(file.fd, buf, { offset: readSize });
            let destinationDistribute = fs.openSync(`${destination}/${file.name}`, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
            while (readLen > 0) {
                readSize += readLen;
                fs.writeSync(destinationDistribute.fd, buf);
                readLen = fs.readSync(file.fd, buf, { offset: readSize });
            }
            fs.closeSync(file);
            fs.closeSync(destinationDistribute);
        }
        catch (err) {
            console.error(FileUtils.tag, `copyFileToDestination failed. Code: ${err.code}, message: ${err.message}`);
        }
    }
    static createPixelMap(uri) {
        let imageInfo;
        let imageResource = undefined;
        let file = undefined;
        try {
            file = fs.openSync(uri, fs.OpenMode.READ_ONLY);
            imageResource = image.createImageSource(file.fd);
            let imageSize = imageResource.getImageInfoSync().size;
            let decodingOptions = FileUtils.getDecodingOptions(imageSize);
            let pixelMap = imageResource.createPixelMapSync(decodingOptions);
            try {
                let orientation = imageResource.getImagePropertySync(image.PropertyKey.ORIENTATION);
                FileUtils.matrixPixelMap(pixelMap, orientation);
            }
            catch (error) {
            }
            imageInfo = { image: pixelMap, url: uri };
            fs.closeSync(file);
            imageResource.release();
        }
        catch (error) {
            fs?.close(file);
            imageResource?.release();
            console.error(FileUtils.tag, `createPixelMap error: ${JSON.stringify(error)}`);
        }
        return imageInfo;
    }
    static getDecodingOptions(size) {
        let width = size.width;
        let height = size.height;
        if (width > height * 3) {
            let x = (width - 3 * height) / 2;
            let y = 0;
            let desiredWidth = Math.max(3 * vp2px(480), 3 * height);
            let desireHeight = Math.max(vp2px(480), height);
            let decodingOptions = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: desiredWidth, height: desireHeight },
                desiredRegion: {
                    x: x,
                    y: y,
                    size: {
                        width: 3 * height,
                        height: height
                    }
                },
                cropAndScaleStrategy: image.CropAndScaleStrategy.CROP_FIRST
            };
            return decodingOptions;
        }
        if (height > width * 3) {
            let y = (height - 3 * width) / 2;
            let x = 0;
            let desiredWidth = Math.max(vp2px(480), width);
            let desireHeight = Math.max(3 * vp2px(480), 3 * width);
            let decodingOptions = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: desiredWidth, height: desireHeight },
                desiredRegion: {
                    x: x,
                    y: y,
                    size: {
                        width: width,
                        height: 3 * width
                    }
                },
                cropAndScaleStrategy: image.CropAndScaleStrategy.CROP_FIRST
            };
            return decodingOptions;
        }
        if (width * height <= 1024 * 1024 * 2) {
            let decodingOptions = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: width, height: height }
            };
            return decodingOptions;
        }
        let widthScale = width / vp2px(480);
        let heightScale = height / vp2px(480);
        if (widthScale > heightScale) {
            let decodingOptions = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: width / heightScale, height: height / heightScale }
            };
            return decodingOptions;
        }
        else {
            let decodingOptions = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: width / widthScale, height: height / widthScale }
            };
            return decodingOptions;
        }
    }
    static matrixPixelMap(pixelMap, orientation) {
        if (orientation == 'Top-right') {
            pixelMap.flipSync(true, false);
        }
        else if (orientation == 'Bottom-right') {
            pixelMap.rotateSync(180);
        }
        else if (orientation == 'Bottom-left') {
            pixelMap.flipSync(false, true);
        }
        else if (orientation == 'Left-top') {
            pixelMap.flipSync(true, false);
            pixelMap.rotateSync(270);
        }
        else if (orientation == 'Right-top') {
            pixelMap.rotateSync(90);
        }
        else if (orientation == 'Right-bottom') {
            pixelMap.flipSync(true, false);
            pixelMap.rotateSync(90);
        }
        else if (orientation == 'Left-bottom') {
            pixelMap.rotateSync(270);
        }
        else if (orientation == 'Top-left') {
        }
    }
    static saveFile(context, buffer) {
        let filesDir = context.filesDir;
        let photoUri = fileUri.getUriFromPath(`${filesDir}/${Date.now().toString()}.${FileUtils.extensionValue}`);
        try {
            let file = fs.openSync(photoUri, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
            fs.writeSync(file.fd, buffer);
            console.debug(FileUtils.tag, `saveFile uri: ${photoUri}}`);
            fs.closeSync(file);
        }
        catch (error) {
            console.error(FileUtils.tag, `saveFile error: ${JSON.stringify(error)}`);
        }
        return photoUri;
    }
}
FileUtils.tag = 'FileUtils';
FileUtils.qualityValue = 98;
FileUtils.formatValue = 'image/jpeg';
FileUtils.extensionValue = 'jpg';
