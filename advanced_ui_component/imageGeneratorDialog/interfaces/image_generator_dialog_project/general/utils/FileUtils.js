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
    static copyFileToDestination(r33, s33) {
        try {
            let u33 = new ArrayBuffer(Constants.FILE_BUFFER_SIZE);
            let v33 = 0;
            let w33 = fs.openSync(r33, fs.OpenMode.READ_ONLY);
            let x33 = fs.readSync(w33.fd, u33, { offset: v33 });
            let y33 = fs.openSync(`${s33}/${w33.name}`, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
            while (x33 > 0) {
                v33 += x33;
                fs.writeSync(y33.fd, u33);
                x33 = fs.readSync(w33.fd, u33, { offset: v33 });
            }
            fs.closeSync(w33);
            fs.closeSync(y33);
        }
        catch (t33) {
            console.error(FileUtils.tag, `copyFileToDestination failed. Code: ${t33.code}, message: ${t33.message}`);
        }
    }
    static createPixelMap(h33) {
        let i33;
        let j33 = undefined;
        let k33 = undefined;
        try {
            k33 = fs.openSync(h33, fs.OpenMode.READ_ONLY);
            j33 = image.createImageSource(k33.fd);
            let m33 = j33.getImageInfoSync().size;
            let n33 = FileUtils.getDecodingOptions(m33);
            let o33 = j33.createPixelMapSync(n33);
            try {
                let q33 = j33.getImagePropertySync(image.PropertyKey.ORIENTATION);
                FileUtils.matrixPixelMap(o33, q33);
            }
            catch (p33) {
            }
            i33 = { image: o33, url: h33 };
            fs.closeSync(k33);
            j33.release();
        }
        catch (l33) {
            fs?.close(k33);
            j33?.release();
            console.error(FileUtils.tag, `createPixelMap error: ${JSON.stringify(l33)}`);
        }
        return i33;
    }
    static getDecodingOptions(p32) {
        let q32 = p32.width;
        let r32 = p32.height;
        if (q32 > r32 * 3) {
            let c33 = (q32 - 3 * r32) / 2;
            let d33 = 0;
            let e33 = Math.max(3 * vp2px(480), 3 * r32);
            let f33 = Math.max(vp2px(480), r32);
            let g33 = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: e33, height: f33 },
                desiredRegion: {
                    x: c33,
                    y: d33,
                    size: {
                        width: 3 * r32,
                        height: r32
                    }
                },
                cropAndScaleStrategy: image.CropAndScaleStrategy.CROP_FIRST
            };
            return g33;
        }
        if (r32 > q32 * 3) {
            let x32 = (r32 - 3 * q32) / 2;
            let y32 = 0;
            let z32 = Math.max(vp2px(480), q32);
            let a33 = Math.max(3 * vp2px(480), 3 * q32);
            let b33 = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: z32, height: a33 },
                desiredRegion: {
                    x: y32,
                    y: x32,
                    size: {
                        width: q32,
                        height: 3 * q32
                    }
                },
                cropAndScaleStrategy: image.CropAndScaleStrategy.CROP_FIRST
            };
            return b33;
        }
        if (q32 * r32 <= 1024 * 1024 * 2) {
            let w32 = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: q32, height: r32 }
            };
            return w32;
        }
        let s32 = q32 / vp2px(480);
        let t32 = r32 / vp2px(480);
        if (s32 > t32) {
            let v32 = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: q32 / t32, height: r32 / t32 }
            };
            return v32;
        }
        else {
            let u32 = {
                index: 0,
                editable: false,
                desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
                desiredSize: { width: q32 / s32, height: r32 / s32 }
            };
            return u32;
        }
    }
    static matrixPixelMap(n32, o32) {
        if (o32 == 'Top-right') {
            n32.flipSync(true, false);
        }
        else if (o32 == 'Bottom-right') {
            n32.rotateSync(180);
        }
        else if (o32 == 'Bottom-left') {
            n32.flipSync(false, true);
        }
        else if (o32 == 'Left-top') {
            n32.flipSync(true, false);
            n32.rotateSync(270);
        }
        else if (o32 == 'Right-top') {
            n32.rotateSync(90);
        }
        else if (o32 == 'Right-bottom') {
            n32.flipSync(true, false);
            n32.rotateSync(90);
        }
        else if (o32 == 'Left-bottom') {
            n32.rotateSync(270);
        }
        else if (o32 == 'Top-left') {
        }
    }
    static saveFile(h32, i32) {
        let j32 = h32.filesDir;
        let k32 = fileUri.getUriFromPath(`${j32}/${Date.now().toString()}.${FileUtils.extensionValue}`);
        try {
            let m32 = fs.openSync(k32, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
            fs.writeSync(m32.fd, i32);
            console.debug(FileUtils.tag, `saveFile uri: ${k32}}`);
            fs.closeSync(m32);
        }
        catch (l32) {
            console.error(FileUtils.tag, `saveFile error: ${JSON.stringify(l32)}`);
        }
        return k32;
    }
}
FileUtils.tag = 'FileUtils';
FileUtils.qualityValue = 98;
FileUtils.formatValue = 'image/jpeg';
FileUtils.extensionValue = 'jpg';
