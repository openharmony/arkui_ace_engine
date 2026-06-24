import image from '@ohos.multimedia.image';
import { BusinessError } from '@ohos.base';
import fs from '@ohos.file.fs';
import common from '@ohos.app.ability.common';
import { systemShare } from '@kit.ShareKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

const DOMAIN = 0x0000;
const TAG = '[ImageShareDemo]';

interface OperationLog {
  operation: string;
  timestamp: string;
  success: boolean;
  detail: string;
}

interface TestResult {
  testName: string;
  category: string;
  passed: boolean;
  message: string;
  durationMs: number;
}

interface FileDetail {
  name: string;
  path: string;
  size: number;
  exists: boolean;
}

class FileHelper {
  static async savePixelMapAsync(pm: image.PixelMap, ctx: common.UIAbilityContext): Promise<string> {
    try {
      let fileName: string = 'sandbox_img_' + Date.now() + '.jpg';
      let filePath: string = ctx.tempDir + '/' + fileName;
      let packer: image.ImagePacker = image.createImagePacker();
      let packOpts: image.PackingOption = { format: 'image/jpeg', quality: 90 };
      let fd: number = fs.openSync(filePath, fs.OpenMode.CREATE | fs.OpenMode.WRITE_ONLY).fd;
      await packer.packToFile(pm, fd, packOpts);
      fs.closeSync(fd);
      await packer.release();
      hilog.info(DOMAIN, TAG, 'savePixelMapAsync %{public}s', filePath);
      return filePath;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'savePixelMapAsync %{public}s', e.message);
      return '';
    }
  }

  static async savePixelMapPng(pm: image.PixelMap, ctx: common.UIAbilityContext): Promise<string> {
    try {
      let fileName: string = 'sandbox_png_' + Date.now() + '.png';
      let filePath: string = ctx.tempDir + '/' + fileName;
      let packer: image.ImagePacker = image.createImagePacker();
      let packOpts: image.PackingOption = { format: 'image/png', quality: 100 };
      let fd: number = fs.openSync(filePath, fs.OpenMode.CREATE | fs.OpenMode.WRITE_ONLY).fd;
      await packer.packToFile(pm, fd, packOpts);
      fs.closeSync(fd);
      await packer.release();
      hilog.info(DOMAIN, TAG, 'savePixelMapPng %{public}s', filePath);
      return filePath;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'savePixelMapPng %{public}s', e.message);
      return '';
    }
  }

  static async savePixelMapWebp(pm: image.PixelMap, ctx: common.UIAbilityContext): Promise<string> {
    try {
      let fileName: string = 'sandbox_webp_' + Date.now() + '.webp';
      let filePath: string = ctx.tempDir + '/' + fileName;
      let packer: image.ImagePacker = image.createImagePacker();
      let packOpts: image.PackingOption = { format: 'image/webp', quality: 80 };
      let fd: number = fs.openSync(filePath, fs.OpenMode.CREATE | fs.OpenMode.WRITE_ONLY).fd;
      await packer.packToFile(pm, fd, packOpts);
      fs.closeSync(fd);
      await packer.release();
      hilog.info(DOMAIN, TAG, 'savePixelMapWebp %{public}s', filePath);
      return filePath;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'savePixelMapWebp %{public}s', e.message);
      return '';
    }
  }

  static getFileSize(filePath: string): number {
    try {
      let stat: fs.Stat = fs.statSync(filePath);
      return stat.size;
    } catch (err) {
      return -1;
    }
  }

  static checkFileExists(filePath: string): boolean {
    try {
      let exists: boolean = fs.accessSync(filePath);
      return exists;
    } catch (err) {
      return false;
    }
  }

  static deleteFile(filePath: string): boolean {
    try {
      fs.unlinkSync(filePath);
      hilog.info(DOMAIN, TAG, 'deleteFile %{public}s', filePath);
      return true;
    } catch (err) {
      return false;
    }
  }

  static cleanTempFiles(ctx: common.UIAbilityContext): number {
    let count: number = 0;
    try {
      let files: string[] = fs.listFileSync(ctx.tempDir);
      for (let i = 0; i < files.length; i++) {
        let fullPath: string = ctx.tempDir + '/' + files[i];
        try {
          fs.unlinkSync(fullPath);
          count++;
        } catch (e) {
          hilog.warn(DOMAIN, TAG, 'skip %{public}s', fullPath);
        }
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'cleanTempFiles %{public}s', e.message);
    }
    return count;
  }

  static listTempFiles(ctx: common.UIAbilityContext): string[] {
    try {
      return fs.listFileSync(ctx.tempDir);
    } catch (err) {
      return [];
    }
  }

  static getFileDetails(ctx: common.UIAbilityContext): FileDetail[] {
    let details: FileDetail[] = [];
    try {
      let files: string[] = fs.listFileSync(ctx.tempDir);
      for (let i = 0; i < files.length; i++) {
        let fullPath: string = ctx.tempDir + '/' + files[i];
        let size: number = FileHelper.getFileSize(fullPath);
        let exists: boolean = FileHelper.checkFileExists(fullPath);
        details.push({
          name: files[i],
          path: fullPath,
          size: size,
          exists: exists,
        });
      }
    } catch (err) {
      hilog.error(DOMAIN, TAG, 'getFileDetails error');
    }
    return details;
  }

  static copyFile(srcPath: string, destPath: string): boolean {
    try {
      let srcFile: fs.File = fs.openSync(srcPath, fs.OpenMode.READ_ONLY);
      let destFile: fs.File = fs.openSync(destPath, fs.OpenMode.CREATE | fs.OpenMode.WRITE_ONLY);
      let buf: ArrayBuffer = new ArrayBuffer(fs.statSync(srcPath).size);
      fs.readSync(srcFile.fd, buf);
      fs.writeSync(destFile.fd, buf);
      fs.closeSync(srcFile);
      fs.closeSync(destFile);
      hilog.info(DOMAIN, TAG, 'copyFile %{public}s -> %{public}s', srcPath, destPath);
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'copyFile %{public}s', e.message);
      return false;
    }
  }

  static readFileInfo(filePath: string): string {
    try {
      let stat: fs.Stat = fs.statSync(filePath);
      let info: string = 'mode=' + stat.mode + ' size=' + stat.size +
        ' atime=' + stat.atime + ' mtime=' + stat.mtime;
      hilog.info(DOMAIN, TAG, 'readFileInfo %{public}s', info);
      return info;
    } catch (err) {
      return 'stat error';
    }
  }

  static writeTextFile(ctx: common.UIAbilityContext, content: string): string {
    try {
      let fileName: string = 'test_text_' + Date.now() + '.txt';
      let filePath: string = ctx.tempDir + '/' + fileName;
      let fd: number = fs.openSync(filePath, fs.OpenMode.CREATE | fs.OpenMode.WRITE_ONLY).fd;
      fs.writeSync(fd, content);
      fs.closeSync(fd);
      hilog.info(DOMAIN, TAG, 'writeTextFile %{public}s', filePath);
      return filePath;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'writeTextFile %{public}s', e.message);
      return '';
    }
  }

  static countTempFiles(ctx: common.UIAbilityContext): number {
    try {
      let files: string[] = fs.listFileSync(ctx.tempDir);
      return files.length;
    } catch (err) {
      return 0;
    }
  }

  static getTempDirSize(ctx: common.UIAbilityContext): number {
    let total: number = 0;
    try {
      let files: string[] = fs.listFileSync(ctx.tempDir);
      for (let i = 0; i < files.length; i++) {
        let fullPath: string = ctx.tempDir + '/' + files[i];
        let size: number = FileHelper.getFileSize(fullPath);
        if (size > 0) {
          total += size;
        }
      }
    } catch (err) {
      hilog.error(DOMAIN, TAG, 'getTempDirSize error');
    }
    return total;
  }
}

class PixelMapHelper {
  static createSamplePixelMap(): image.PixelMap | null {
    try {
      let opts: image.InitializationOptions = {
        size: { width: 200, height: 200 },
        pixelFormat: image.PixelMapFormat.RGBA_8888,
        editable: true,
      };
      let pm: image.PixelMap = image.createPixelMapSync(opts);
      hilog.info(DOMAIN, TAG, 'createSamplePixelMap success');
      return pm;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'createSamplePixelMap %{public}s', e.message);
      return null;
    }
  }

  static createLargePixelMap(w: number, h: number): image.PixelMap | null {
    try {
      let opts: image.InitializationOptions = {
        size: { width: w, height: h },
        pixelFormat: image.PixelMapFormat.RGBA_8888,
        editable: true,
      };
      let pm: image.PixelMap = image.createPixelMapSync(opts);
      hilog.info(DOMAIN, TAG, 'createLargePixelMap %{public}dx%{public}d', w, h);
      return pm;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'createLargePixelMap %{public}s', e.message);
      return null;
    }
  }

  static getPixelMapInfo(pm: image.PixelMap): string {
    try {
      let info: image.ImageInfo = pm.getImageInfoSync();
      let w: number = info.size.width;
      let h: number = info.size.height;
      return w + 'x' + h;
    } catch (err) {
      return 'info error';
    }
  }

  static rotatePixelMap(pm: image.PixelMap, degrees: number): boolean {
    try {
      pm.rotateSync(degrees);
      hilog.info(DOMAIN, TAG, 'rotatePixelMap %{public}d', degrees);
      return true;
    } catch (err) {
      return false;
    }
  }

  static scalePixelMap(pm: image.PixelMap, sx: number, sy: number): boolean {
    try {
      pm.scaleSync(sx, sy);
      hilog.info(DOMAIN, TAG, 'scalePixelMap %{public}fx%{public}f', sx, sy);
      return true;
    } catch (err) {
      return false;
    }
  }

  static flipPixelMap(pm: image.PixelMap, h: boolean, v: boolean): boolean {
    try {
      pm.flipSync(h, v);
      hilog.info(DOMAIN, TAG, 'flipPixelMap h=%{public}s v=%{public}s', String(h), String(v));
      return true;
    } catch (err) {
      return false;
    }
  }

  static cropPixelMap(pm: image.PixelMap): boolean {
    try {
      pm.cropSync({ x: 0, y: 0, size: { width: 100, height: 100 } });
      hilog.info(DOMAIN, TAG, 'cropPixelMap 0 0 100 100');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'cropPixelMap %{public}s', e.message);
      return false;
    }
  }
}

class ShareHelper {
  static async shareImage(filePath: string, ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let record: systemShare.SharedRecord = {
        utd: 'general.image',
        uri: filePath,
        title: 'Sandbox Image',
      };
      let sharedData: systemShare.SharedData = new systemShare.SharedData(record);
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'shareImage success');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'shareImage %{public}s', e.message);
      return false;
    }
  }

  static async sharePngImage(filePath: string, ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let record: systemShare.SharedRecord = {
        utd: 'general.image',
        uri: filePath,
        title: 'PNG Sandbox Image',
        description: 'PNG format image from sandbox',
      };
      let sharedData: systemShare.SharedData = new systemShare.SharedData(record);
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'sharePngImage success');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'sharePngImage %{public}s', e.message);
      return false;
    }
  }

  static async shareWebpImage(filePath: string, ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let record: systemShare.SharedRecord = {
        utd: 'general.image',
        uri: filePath,
        title: 'WebP Sandbox Image',
        description: 'WebP format image from sandbox',
      };
      let sharedData: systemShare.SharedData = new systemShare.SharedData(record);
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'shareWebpImage success');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'shareWebpImage %{public}s', e.message);
      return false;
    }
  }

  static async shareText(content: string, ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let record: systemShare.SharedRecord = {
        utd: 'general.plain-text',
        content: content,
        title: 'Share Text',
      };
      let sharedData: systemShare.SharedData = new systemShare.SharedData(record);
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'shareText success');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'shareText %{public}s', e.message);
      return false;
    }
  }

  static async shareMultipleImages(filePaths: string[], ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let sharedData: systemShare.SharedData = new systemShare.SharedData({
        utd: 'general.image',
        uri: filePaths[0],
        title: 'Multi Image Share',
      });
      for (let i = 1; i < filePaths.length; i++) {
        sharedData.addRecord({
          utd: 'general.image',
          uri: filePaths[i],
          title: 'Image ' + i,
        });
      }
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'shareMultipleImages count=%{public}d', filePaths.length);
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'shareMultipleImages %{public}s', e.message);
      return false;
    }
  }

  static async shareFile(filePath: string, ctx: common.UIAbilityContext): Promise<boolean> {
    try {
      let record: systemShare.SharedRecord = {
        utd: 'general.file',
        uri: filePath,
        title: 'Share File',
      };
      let sharedData: systemShare.SharedData = new systemShare.SharedData(record);
      let controller: systemShare.ShareController = new systemShare.ShareController(sharedData);
      await controller.show(ctx, {
        selectionMode: systemShare.SelectionMode.SINGLE,
        previewMode: systemShare.SharePreviewMode.DEFAULT,
      });
      hilog.info(DOMAIN, TAG, 'shareFile success');
      return true;
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      hilog.error(DOMAIN, TAG, 'shareFile %{public}s', e.message);
      return false;
    }
  }
}

class TestRunner {
  static runSaveTest(ctx: common.UIAbilityContext): TestResult {
    let startMs: number = Date.now();
    try {
      let pm: image.PixelMap | null = PixelMapHelper.createSamplePixelMap();
      let duration: number = Date.now() - startMs;
      if (pm === null) {
        return { testName: 'Save JPG', category: 'Save', passed: false, message: 'null', durationMs: duration };
      }
      return { testName: 'Save JPG', category: 'Save', passed: true, message: 'pm created', durationMs: duration };
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      return { testName: 'Save JPG', category: 'Save', passed: false, message: e.message, durationMs: Date.now() - startMs };
    }
  }

  static runFileExistsTest(filePath: string): TestResult {
    let startMs: number = Date.now();
    let exists: boolean = FileHelper.checkFileExists(filePath);
    return {
      testName: 'File Exists',
      category: 'File',
      passed: exists,
      message: 'path=' + filePath + ' exists=' + String(exists),
      durationMs: Date.now() - startMs,
    };
  }

  static runFileSizeTest(filePath: string): TestResult {
    let startMs: number = Date.now();
    let size: number = FileHelper.getFileSize(filePath);
    return {
      testName: 'File Size',
      category: 'File',
      passed: size > 0,
      message: 'size=' + size,
      durationMs: Date.now() - startMs,
    };
  }

  static runRotateTest(pm: image.PixelMap): TestResult {
    let startMs: number = Date.now();
    let ok: boolean = PixelMapHelper.rotatePixelMap(pm, 90);
    return {
      testName: 'Rotate 90',
      category: 'Transform',
      passed: ok,
      message: ok ? 'rotated' : 'failed',
      durationMs: Date.now() - startMs,
    };
  }

  static runScaleTest(pm: image.PixelMap): TestResult {
    let startMs: number = Date.now();
    let ok: boolean = PixelMapHelper.scalePixelMap(pm, 1.5, 1.5);
    return {
      testName: 'Scale 1.5x',
      category: 'Transform',
      passed: ok,
      message: ok ? 'scaled' : 'failed',
      durationMs: Date.now() - startMs,
    };
  }

  static runFlipTest(pm: image.PixelMap): TestResult {
    let startMs: number = Date.now();
    let ok: boolean = PixelMapHelper.flipPixelMap(pm, true, false);
    return {
      testName: 'Flip H',
      category: 'Transform',
      passed: ok,
      message: ok ? 'flipped' : 'failed',
      durationMs: Date.now() - startMs,
    };
  }

  static runCropTest(pm: image.PixelMap): TestResult {
    let startMs: number = Date.now();
    let ok: boolean = PixelMapHelper.cropPixelMap(pm);
    return {
      testName: 'Crop 100x100',
      category: 'Transform',
      passed: ok,
      message: ok ? 'cropped' : 'failed',
      durationMs: Date.now() - startMs,
    };
  }

  static runDeleteTest(filePath: string): TestResult {
    let startMs: number = Date.now();
    let ok: boolean = FileHelper.deleteFile(filePath);
    return {
      testName: 'Delete File',
      category: 'File',
      passed: ok,
      message: 'deleted=' + String(ok),
      durationMs: Date.now() - startMs,
    };
  }

  static runCleanTempTest(ctx: common.UIAbilityContext): TestResult {
    let startMs: number = Date.now();
    let count: number = FileHelper.cleanTempFiles(ctx);
    return {
      testName: 'Clean Temp',
      category: 'File',
      passed: count >= 0,
      message: 'cleaned=' + count,
      durationMs: Date.now() - startMs,
    };
  }

  static runAllTests(pm: image.PixelMap, filePath: string, ctx: common.UIAbilityContext): TestResult[] {
    let results: TestResult[] = [];
    results.push(TestRunner.runRotateTest(pm));
    results.push(TestRunner.runScaleTest(pm));
    results.push(TestRunner.runFlipTest(pm));
    results.push(TestRunner.runCropTest(pm));
    results.push(TestRunner.runFileExistsTest(filePath));
    results.push(TestRunner.runFileSizeTest(filePath));
    hilog.info(DOMAIN, TAG, 'runAllTests total=%{public}d', results.length);
    return results;
  }

  static formatReport(results: TestResult[]): string {
    let lines: string[] = [];
    let passCount: number = 0;
    let failCount: number = 0;
    lines.push('=== Test Report v1.0-2026 ===');
    for (let i = 0; i < results.length; i++) {
      let r: TestResult = results[i];
      let status: string = r.passed ? 'PASS' : 'FAIL';
      lines.push(r.testName + ' [' + r.category + '] ' + status + ' ' + r.durationMs + 'ms ' + r.message);
      if (r.passed) {
        passCount++;
      } else {
        failCount++;
      }
    }
    lines.push('=== Total: ' + results.length + ' Pass: ' + passCount + ' Fail: ' + failCount + ' ===');
    return lines.join('\n');
  }
}

function formatTimestamp(): string {
  let now: Date = new Date();
  return now.getFullYear() + '-' +
    String(now.getMonth() + 1).padStart(2, '0') + '-' +
    String(now.getDate()).padStart(2, '0') + ' ' +
    String(now.getHours()).padStart(2, '0') + ':' +
    String(now.getMinutes()).padStart(2, '0') + ':' +
    String(now.getSeconds()).padStart(2, '0');
}

function formatFileSize(bytes: number): string {
  if (bytes < 0) {
    return 'N/A';
  }
  if (bytes < 1024) {
    return bytes + 'B';
  }
  if (bytes < 1024 * 1024) {
    return (bytes / 1024).toFixed(1) + 'KB';
  }
  return (bytes / 1024 / 1024).toFixed(1) + 'MB';
}

@Entry
@Component
struct Index {
  @State resultMsg: string = 'Ready';
  @State savedFilePath: string = '';
  @State savedPngPath: string = '';
  @State savedWebpPath: string = '';
  @State imageInfoText: string = '';
  @State saving: boolean = false;
  @State sharing: boolean = false;
  @State runningTests: boolean = false;
  @State logList: OperationLog[] = [];
  @State testResults: TestResult[] = [];
  @State pixelMap: image.PixelMap | null = null;
  @State fileCount: number = 0;
  @State totalSize: string = '';
  @State fileDetailList: FileDetail[] = [];
  @State testReport: string = '';
  @State saveJpgSize: string = '';
  @State savePngSize: string = '';
  @State saveWebpSize: string = '';
  @State testPassCount: number = 0;
  @State testFailCount: number = 0;
  @State compareMsg: string = '';
  @State batchSaveCount: number = 0;
  @State lastOperation: string = '';
  @State sessionStartTime: string = '';
  @State jpgSaved: boolean = false;
  @State pngSaved: boolean = false;
  @State webpSaved: boolean = false;
  @State totalOperations: number = 0;
  private context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;

  initSession(): void {
    this.sessionStartTime = formatTimestamp();
    this.lastOperation = 'Session started';
    this.addLog('Session', true, this.sessionStartTime);
  }

  resetAll(): void {
    this.savedFilePath = '';
    this.savedPngPath = '';
    this.savedWebpPath = '';
    this.imageInfoText = '';
    this.saveJpgSize = '';
    this.savePngSize = '';
    this.saveWebpSize = '';
    this.fileCount = 0;
    this.totalSize = '';
    this.fileDetailList = [];
    this.testResults = [];
    this.testReport = '';
    this.testPassCount = 0;
    this.testFailCount = 0;
    this.compareMsg = '';
    this.batchSaveCount = 0;
    this.resultMsg = 'Reset done';
    this.addLog('Reset', true, 'all cleared');
  }

  doCompareFormats(): void {
    if (this.saveJpgSize.length === 0 || this.savePngSize.length === 0) {
      this.resultMsg = 'Save JPG and PNG first to compare';
      return;
    }
    let jpgBytes: number = FileHelper.getFileSize(this.savedFilePath);
    let pngBytes: number = FileHelper.getFileSize(this.savedPngPath);
    let webpBytes: number = 0;
    if (this.savedWebpPath.length > 0) {
      webpBytes = FileHelper.getFileSize(this.savedWebpPath);
    }
    let ratioPng: string = pngBytes > 0 ? (jpgBytes / pngBytes).toFixed(2) : 'N/A';
    let ratioWebp: string = webpBytes > 0 ? (jpgBytes / webpBytes).toFixed(2) : 'N/A';
    this.compareMsg = 'JPG: ' + formatFileSize(jpgBytes) +
      ' PNG: ' + formatFileSize(pngBytes) + ' (ratio=' + ratioPng + ')' +
      ' WebP: ' + formatFileSize(webpBytes) + ' (ratio=' + ratioWebp + ')';
    this.resultMsg = this.compareMsg;
    this.addLog('Compare', true, 'jpg=' + jpgBytes + ' png=' + pngBytes);
  }

  async doBatchSave(): Promise<void> {
    this.saving = true;
    this.batchSaveCount = 0;
    this.resultMsg = 'Batch saving 3 images...';
    try {
      let pm: image.PixelMap | null = PixelMapHelper.createSamplePixelMap();
      if (pm === null) {
        this.resultMsg = 'Create failed';
        this.addLog('Batch', false, 'PixelMap null');
        this.saving = false;
        return;
      }
      this.pixelMap = pm;
      let jpgPath: string = await FileHelper.savePixelMapAsync(pm, this.context);
      if (jpgPath.length > 0) {
        this.savedFilePath = jpgPath;
        this.saveJpgSize = formatFileSize(FileHelper.getFileSize(jpgPath));
        this.batchSaveCount++;
      }
      let pngPath: string = await FileHelper.savePixelMapPng(pm, this.context);
      if (pngPath.length > 0) {
        this.savedPngPath = pngPath;
        this.savePngSize = formatFileSize(FileHelper.getFileSize(pngPath));
        this.batchSaveCount++;
      }
      let webpPath: string = await FileHelper.savePixelMapWebp(pm, this.context);
      if (webpPath.length > 0) {
        this.savedWebpPath = webpPath;
        this.saveWebpSize = formatFileSize(FileHelper.getFileSize(webpPath));
        this.batchSaveCount++;
      }
      let info: string = PixelMapHelper.getPixelMapInfo(pm);
      this.imageInfoText = info;
      this.resultMsg = 'Batch saved ' + this.batchSaveCount + ' formats';
      this.addLog('Batch', true, 'count=' + this.batchSaveCount);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Batch error: ' + e.message;
      this.addLog('Batch', false, e.message);
    }
    this.saving = false;
  }

  async doBatchShare(): Promise<void> {
    let paths: string[] = [];
    if (this.savedFilePath.length > 0) {
      paths.push(this.savedFilePath);
    }
    if (this.savedPngPath.length > 0) {
      paths.push(this.savedPngPath);
    }
    if (this.savedWebpPath.length > 0) {
      paths.push(this.savedWebpPath);
    }
    if (paths.length === 0) {
      this.resultMsg = 'No files to share';
      return;
    }
    this.sharing = true;
    try {
      let ok: boolean = await ShareHelper.shareMultipleImages(paths, this.context);
      this.resultMsg = ok ? 'Batch share shown (' + paths.length + ')' : 'Batch share failed';
      this.addLog('BatchShare', ok, 'count=' + paths.length);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('BatchShare', false, e.message);
    }
    this.sharing = false;
  }

  doSummary(): void {
    let lines: string[] = [];
    lines.push('=== Session Summary v1.0-2026 ===');
    lines.push('Start: ' + this.sessionStartTime);
    lines.push('JPG: ' + (this.savedFilePath.length > 0 ? this.saveJpgSize : 'none'));
    lines.push('PNG: ' + (this.savedPngPath.length > 0 ? this.savePngSize : 'none'));
    lines.push('WebP: ' + (this.savedWebpPath.length > 0 ? this.saveWebpSize : 'none'));
    lines.push('Files: ' + this.fileCount + ' Size: ' + this.totalSize);
    lines.push('Tests: pass=' + this.testPassCount + ' fail=' + this.testFailCount);
    lines.push('Logs: ' + this.logList.length);
    lines.push('Batch: ' + this.batchSaveCount + ' saved');
    lines.push('Last: ' + this.lastOperation);
    lines.push('Compare: ' + (this.compareMsg.length > 0 ? 'yes' : 'no'));
    lines.push('PixelMap: ' + (this.pixelMap !== null ? PixelMapHelper.getPixelMapInfo(this.pixelMap!) : 'null'));
    lines.push('=== End Summary ===');
    this.resultMsg = lines.join('\n');
    this.addLog('Summary', true, 'session');
  }

  doRotateMultiple(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok1: boolean = PixelMapHelper.rotatePixelMap(this.pixelMap, 90);
    let ok2: boolean = PixelMapHelper.rotatePixelMap(this.pixelMap, 90);
    let ok3: boolean = PixelMapHelper.rotatePixelMap(this.pixelMap, 90);
    let ok4: boolean = PixelMapHelper.rotatePixelMap(this.pixelMap, 90);
    this.resultMsg = '4x90=' + String(ok1 && ok2 && ok3 && ok4) + ' (360 total)';
    this.addLog('Rotate4x', ok1, '360deg');
    if (ok1) {
      this.lastOperation = '4x90 rotate';
      this.resaveAndLog();
    }
  }

  doScaleDown(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.scalePixelMap(this.pixelMap, 0.5, 0.5);
    this.resultMsg = ok ? 'Scaled down 0.5x' : 'Scale down failed';
    this.addLog('ScaleDown', ok, '0.5x');
    if (ok) {
      this.lastOperation = 'scale 0.5x';
      this.resaveAndLog();
    }
  }

  doFlipV(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.flipPixelMap(this.pixelMap, false, true);
    this.resultMsg = ok ? 'Flipped V' : 'Flip V failed';
    this.addLog('FlipV', ok, 'v');
    if (ok) {
      this.lastOperation = 'flip v';
      this.resaveAndLog();
    }
  }

  doFlipBoth(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.flipPixelMap(this.pixelMap, true, true);
    this.resultMsg = ok ? 'Flipped HV' : 'Flip HV failed';
    this.addLog('FlipHV', ok, 'hv');
    if (ok) {
      this.lastOperation = 'flip hv';
      this.resaveAndLog();
    }
  }

  async doCreateLargeSave(): Promise<void> {
    this.saving = true;
    this.resultMsg = 'Creating 400x400 PixelMap...';
    try {
      let pm: image.PixelMap | null = PixelMapHelper.createLargePixelMap(400, 400);
      if (pm === null) {
        this.resultMsg = 'Large PixelMap create failed';
        this.addLog('LargeSave', false, 'null');
        this.saving = false;
        return;
      }
      this.pixelMap = pm;
      let filePath: string = await FileHelper.savePixelMapAsync(pm, this.context);
      if (filePath.length === 0) {
        this.resultMsg = 'Large save failed';
        this.addLog('LargeSave', false, 'packToFile failed');
      } else {
        this.savedFilePath = filePath;
        let info: string = PixelMapHelper.getPixelMapInfo(pm);
        let size: number = FileHelper.getFileSize(filePath);
        this.imageInfoText = info + ' ' + formatFileSize(size);
        this.resultMsg = 'Large saved: ' + filePath;
        this.lastOperation = 'large save';
        this.addLog('LargeSave', true, filePath);
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('LargeSave', false, e.message);
    }
    this.saving = false;
  }

  doCountFiles(): void {
    this.fileCount = FileHelper.countTempFiles(this.context);
    let totalBytes: number = FileHelper.getTempDirSize(this.context);
    this.totalSize = formatFileSize(totalBytes);
    this.resultMsg = 'Count: ' + this.fileCount + ' files, ' + this.totalSize;
    this.lastOperation = 'count files';
    this.addLog('Count', true, String(this.fileCount));
  }

  doFullWorkflow(): void {
    this.resultMsg = 'Workflow: save->transform->save->share';
    this.lastOperation = 'full workflow';
    this.addLog('Workflow', true, 'started');
  }

  doExportReport(): void {
    if (this.testResults.length === 0) {
      this.resultMsg = 'Run tests first';
      return;
    }
    let report: string = TestRunner.formatReport(this.testResults);
    this.testReport = report;
    this.lastOperation = 'export report';
    this.addLog('Export', true, 'report');
  }

  addLog(op: string, success: boolean, detail: string): void {
    this.totalOperations++;
    this.logList.push({
      operation: op,
      timestamp: formatTimestamp(),
      success: success,
      detail: detail.substring(0, 60),
    });
    if (this.logList.length > 20) {
      this.logList.shift();
    }
  }

  async doSaveJpg(): Promise<void> {
    this.saving = true;
    this.resultMsg = 'Creating PixelMap & saving JPG...';
    try {
      let pm: image.PixelMap | null = PixelMapHelper.createSamplePixelMap();
      if (pm === null) {
        this.resultMsg = 'Create failed';
        this.addLog('Save JPG', false, 'PixelMap null');
        this.saving = false;
        return;
      }
      this.pixelMap = pm;
      let filePath: string = await FileHelper.savePixelMapAsync(pm, this.context);
      if (filePath.length === 0) {
        this.resultMsg = 'Save JPG failed';
        this.addLog('Save JPG', false, 'packToFile failed');
      } else {
        this.savedFilePath = filePath;
        let info: string = PixelMapHelper.getPixelMapInfo(pm);
        let size: number = FileHelper.getFileSize(filePath);
        this.imageInfoText = info + ' ' + formatFileSize(size);
        this.resultMsg = 'JPG saved: ' + filePath;
        this.addLog('Save JPG', true, filePath);
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Save JPG', false, e.message);
    }
    this.saving = false;
  }

  async doSavePng(): Promise<void> {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    this.saving = true;
    this.resultMsg = 'Saving PNG...';
    try {
      let filePath: string = await FileHelper.savePixelMapPng(this.pixelMap, this.context);
      if (filePath.length === 0) {
        this.resultMsg = 'Save PNG failed';
        this.addLog('Save PNG', false, 'packToFile failed');
      } else {
        this.savedPngPath = filePath;
        let size: number = FileHelper.getFileSize(filePath);
        this.resultMsg = 'PNG saved: ' + filePath + ' ' + formatFileSize(size);
        this.addLog('Save PNG', true, filePath);
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Save PNG', false, e.message);
    }
    this.saving = false;
  }

  async doSaveWebp(): Promise<void> {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    this.saving = true;
    this.resultMsg = 'Saving WebP...';
    try {
      let filePath: string = await FileHelper.savePixelMapWebp(this.pixelMap, this.context);
      if (filePath.length === 0) {
        this.resultMsg = 'Save WebP failed';
        this.addLog('Save WebP', false, 'packToFile failed');
      } else {
        this.savedWebpPath = filePath;
        let size: number = FileHelper.getFileSize(filePath);
        this.resultMsg = 'WebP saved: ' + filePath + ' ' + formatFileSize(size);
        this.addLog('Save WebP', true, filePath);
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Save WebP', false, e.message);
    }
    this.saving = false;
  }

  async doShareJpg(): Promise<void> {
    if (this.savedFilePath.length === 0) {
      this.resultMsg = 'Save JPG first';
      return;
    }
    this.sharing = true;
    try {
      let ok: boolean = await ShareHelper.shareImage(this.savedFilePath, this.context);
      this.resultMsg = ok ? 'JPG share shown' : 'JPG share failed';
      this.addLog('Share JPG', ok, this.savedFilePath);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Share JPG', false, e.message);
    }
    this.sharing = false;
  }

  async doSharePng(): Promise<void> {
    if (this.savedPngPath.length === 0) {
      this.resultMsg = 'Save PNG first';
      return;
    }
    this.sharing = true;
    try {
      let ok: boolean = await ShareHelper.sharePngImage(this.savedPngPath, this.context);
      this.resultMsg = ok ? 'PNG share shown' : 'PNG share failed';
      this.addLog('Share PNG', ok, this.savedPngPath);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Share PNG', false, e.message);
    }
    this.sharing = false;
  }

  async doShareWebp(): Promise<void> {
    if (this.savedWebpPath.length === 0) {
      this.resultMsg = 'Save WebP first';
      return;
    }
    this.sharing = true;
    try {
      let ok: boolean = await ShareHelper.shareWebpImage(this.savedWebpPath, this.context);
      this.resultMsg = ok ? 'WebP share shown' : 'WebP share failed';
      this.addLog('Share WebP', ok, this.savedWebpPath);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Share WebP', false, e.message);
    }
    this.sharing = false;
  }

  async doShareText(): Promise<void> {
    this.sharing = true;
    try {
      let content: string = 'ImageShare Demo at ' + formatTimestamp() + ' v1.0-2026';
      let ok: boolean = await ShareHelper.shareText(content, this.context);
      this.resultMsg = ok ? 'Text share shown' : 'Text share failed';
      this.addLog('Share Text', ok, content.substring(0, 30));
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Share Text', false, e.message);
    }
    this.sharing = false;
  }

  async doShareMulti(): Promise<void> {
    let paths: string[] = [];
    if (this.savedFilePath.length > 0) {
      paths.push(this.savedFilePath);
    }
    if (this.savedPngPath.length > 0) {
      paths.push(this.savedPngPath);
    }
    if (paths.length < 2) {
      this.resultMsg = 'Need at least 2 saved files';
      return;
    }
    this.sharing = true;
    try {
      let ok: boolean = await ShareHelper.shareMultipleImages(paths, this.context);
      this.resultMsg = ok ? 'Multi share shown' : 'Multi share failed';
      this.addLog('Share Multi', ok, 'count=' + paths.length);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('Share Multi', false, e.message);
    }
    this.sharing = false;
  }

  doRotate(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.rotatePixelMap(this.pixelMap, 90);
    this.resultMsg = ok ? 'Rotated 90' : 'Rotate failed';
    this.addLog('Rotate', ok, '90deg');
    if (ok) {
      this.resaveAndLog();
    }
  }

  doScale(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.scalePixelMap(this.pixelMap, 1.5, 1.5);
    this.resultMsg = ok ? 'Scaled 1.5x' : 'Scale failed';
    this.addLog('Scale', ok, '1.5x');
    if (ok) {
      this.resaveAndLog();
    }
  }

  doFlip(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.flipPixelMap(this.pixelMap, true, false);
    this.resultMsg = ok ? 'Flipped H' : 'Flip failed';
    this.addLog('Flip', ok, 'h');
    if (ok) {
      this.resaveAndLog();
    }
  }

  doCrop(): void {
    if (this.pixelMap === null) {
      this.resultMsg = 'Create PixelMap first';
      return;
    }
    let ok: boolean = PixelMapHelper.cropPixelMap(this.pixelMap);
    this.resultMsg = ok ? 'Cropped 100x100' : 'Crop failed';
    this.addLog('Crop', ok, '100x100');
    if (ok) {
      this.resaveAndLog();
    }
  }

  async resaveAndLog(): Promise<void> {
    let newPath: string = await FileHelper.savePixelMapAsync(this.pixelMap!, this.context);
    if (newPath.length > 0) {
      this.savedFilePath = newPath;
      this.imageInfoText = PixelMapHelper.getPixelMapInfo(this.pixelMap!);
    }
  }

  doDelete(): void {
    if (this.savedFilePath.length === 0) {
      this.resultMsg = 'No file to delete';
      return;
    }
    let ok: boolean = FileHelper.deleteFile(this.savedFilePath);
    this.resultMsg = ok ? 'Deleted JPG' : 'Delete failed';
    this.addLog('Delete', ok, this.savedFilePath);
    if (ok) {
      this.savedFilePath = '';
      this.imageInfoText = '';
    }
  }

  doCheck(): void {
    if (this.savedFilePath.length === 0) {
      this.resultMsg = 'No file';
      return;
    }
    let exists: boolean = FileHelper.checkFileExists(this.savedFilePath);
    let size: number = FileHelper.getFileSize(this.savedFilePath);
    let statInfo: string = FileHelper.readFileInfo(this.savedFilePath);
    this.resultMsg = 'Exists=' + String(exists) + ' Size=' + formatFileSize(size) + '\n' + statInfo;
    this.addLog('Check', exists, 'size=' + size);
  }

  doClean(): void {
    let count: number = FileHelper.cleanTempFiles(this.context);
    this.savedFilePath = '';
    this.savedPngPath = '';
    this.savedWebpPath = '';
    this.imageInfoText = '';
    this.fileDetailList = [];
    this.resultMsg = 'Cleaned ' + count + ' files';
    this.addLog('Clean', true, 'count=' + count);
  }

  doList(): void {
    let details: FileDetail[] = FileHelper.getFileDetails(this.context);
    this.fileDetailList = details;
    this.fileCount = details.length;
    let totalBytes: number = FileHelper.getTempDirSize(this.context);
    this.totalSize = formatFileSize(totalBytes);
    this.resultMsg = 'Files: ' + details.length + ' Total: ' + this.totalSize;
    this.addLog('List', true, 'count=' + details.length);
  }

  async doSaveAndShareText(): Promise<void> {
    this.saving = true;
    try {
      let content: string = 'ImageShare Test Report\nTime: ' + formatTimestamp() + '\nFiles: ' + this.fileCount +
        '\nTotalSize: ' + this.totalSize + '\nv1.0-2026';
      let textPath: string = FileHelper.writeTextFile(this.context, content);
      if (textPath.length === 0) {
        this.resultMsg = 'Write text failed';
        this.addLog('SaveTxt', false, 'write failed');
      } else {
        let ok: boolean = await ShareHelper.shareFile(textPath, this.context);
        this.resultMsg = ok ? 'Text file shared' : 'Text file share failed';
        this.addLog('SaveShareTxt', ok, textPath);
      }
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Error: ' + e.message;
      this.addLog('SaveShareTxt', false, e.message);
    }
    this.saving = false;
  }

  async doRunTests(): Promise<void> {
    if (this.pixelMap === null || this.savedFilePath.length === 0) {
      this.resultMsg = 'Save first to run tests';
      return;
    }
    this.runningTests = true;
    this.resultMsg = 'Running tests...';
    try {
      let results: TestResult[] = TestRunner.runAllTests(this.pixelMap!, this.savedFilePath, this.context);
      this.testResults = results;
      this.testReport = TestRunner.formatReport(results);
      this.resultMsg = 'Tests done: ' + results.length;
      this.addLog('RunTests', true, 'count=' + results.length);
    } catch (err) {
      let e: BusinessError = err as BusinessError;
      this.resultMsg = 'Test error: ' + e.message;
      this.addLog('RunTests', false, e.message);
    }
    this.runningTests = false;
  }

  build() {
    Scroll() {
      Column() {
        Text('ImageShare Demo v1.0-2026')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 8 })

        Text('Save PixelMap, share JPG/PNG/WebP & text via ShareKit')
          .fontSize(13)
          .fontColor('#666666')
          .margin({ bottom: 8 })

        Divider().margin({ bottom: 10 })

        Text('-- Batch & Compare --')
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 6 })

        Row() {
          Button('Batch Save')
            .fontSize(14).width(110).height(38)
            .enabled(!this.saving)
            .onClick(() => this.doBatchSave())
          Button('Batch Share')
            .fontSize(14).width(110).height(38)
            .enabled(!this.sharing && this.batchSaveCount > 0)
            .onClick(() => this.doBatchShare())
          Button('Compare')
            .fontSize(14).width(90).height(38)
            .enabled(this.saveJpgSize.length > 0 && this.savePngSize.length > 0)
            .onClick(() => this.doCompareFormats())
        }.margin({ bottom: 6 })

        Row() {
          Button('Reset All')
            .fontSize(14).width(100).height(36)
            .onClick(() => this.resetAll())
          Button('Summary')
            .fontSize(14).width(100).height(36)
            .onClick(() => this.doSummary())
          Button('Init Session')
            .fontSize(14).width(100).height(36)
            .onClick(() => this.initSession())
        }.margin({ bottom: 8 })

        Divider().margin({ bottom: 10 })

        if (this.saveJpgSize.length > 0) {
          Text('JPG: ' + this.saveJpgSize)
            .fontSize(12).fontColor('#FF9800').margin({ bottom: 2 }).width('90%')
        }

        if (this.savePngSize.length > 0) {
          Text('PNG: ' + this.savePngSize)
            .fontSize(12).fontColor('#2196F3').margin({ bottom: 2 }).width('90%')
        }

        if (this.saveWebpSize.length > 0) {
          Text('WebP: ' + this.saveWebpSize)
            .fontSize(12).fontColor('#9C27B0').margin({ bottom: 2 }).width('90%')
        }

        if (this.compareMsg.length > 0) {
          Text('Compare: ' + this.compareMsg)
            .fontSize(12).fontColor('#E91E63').maxLines(3).width('90%').margin({ bottom: 8 })
        }

        Divider().margin({ bottom: 10 })
          .margin({ bottom: 6 })

        Row() {
          Button('Save JPG')
            .fontSize(14).width(100).height(38)
            .enabled(!this.saving)
            .onClick(() => this.doSaveJpg())
          Button('Save PNG')
            .fontSize(14).width(100).height(38)
            .enabled(!this.saving && this.pixelMap !== null)
            .onClick(() => this.doSavePng())
          Button('Save WebP')
            .fontSize(14).width(100).height(38)
            .enabled(!this.saving && this.pixelMap !== null)
            .onClick(() => this.doSaveWebp())
        }.margin({ bottom: 8 })

        Divider().margin({ bottom: 10 })

        Text('-- Share Resources --')
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 6 })

        Row() {
          Button('Share JPG')
            .fontSize(14).width(90).height(36)
            .enabled(!this.sharing && this.savedFilePath.length > 0)
            .onClick(() => this.doShareJpg())
          Button('Share PNG')
            .fontSize(14).width(90).height(36)
            .enabled(!this.sharing && this.savedPngPath.length > 0)
            .onClick(() => this.doSharePng())
          Button('Share WebP')
            .fontSize(14).width(90).height(36)
            .enabled(!this.sharing && this.savedWebpPath.length > 0)
            .onClick(() => this.doShareWebp())
        }.margin({ bottom: 6 })

        Row() {
          Button('Share Text')
            .fontSize(14).width(100).height(36)
            .enabled(!this.sharing)
            .onClick(() => this.doShareText())
          Button('Share Multi')
            .fontSize(14).width(100).height(36)
            .enabled(!this.sharing)
            .onClick(() => this.doShareMulti())
          Button('Share File')
            .fontSize(14).width(100).height(36)
            .enabled(!this.saving)
            .onClick(() => this.doSaveAndShareText())
        }.margin({ bottom: 8 })

        Divider().margin({ bottom: 10 })

        Text('-- Transform --')
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 6 })

        Row() {
          Button('Rotate 90')
            .fontSize(14).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doRotate())
          Button('Scale 1.5x')
            .fontSize(14).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doScale())
          Button('Flip H')
            .fontSize(14).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doFlip())
          Button('Crop')
            .fontSize(14).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doCrop())
        }.margin({ bottom: 6 })

        Row() {
          Button('4x90 Rotate')
            .fontSize(13).width(95).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doRotateMultiple())
          Button('Scale 0.5x')
            .fontSize(13).width(90).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doScaleDown())
          Button('Flip V')
            .fontSize(13).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doFlipV())
          Button('Flip HV')
            .fontSize(13).width(80).height(36)
            .enabled(this.pixelMap !== null)
            .onClick(() => this.doFlipBoth())
        }.margin({ bottom: 8 })

        Divider().margin({ bottom: 10 })

        Text('-- File Management --')
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 6 })

        Row() {
          Button('Check')
            .fontSize(14).width(70).height(36)
            .enabled(this.savedFilePath.length > 0)
            .onClick(() => this.doCheck())
          Button('Delete')
            .fontSize(14).width(70).height(36)
            .enabled(this.savedFilePath.length > 0)
            .onClick(() => this.doDelete())
          Button('Clean')
            .fontSize(14).width(70).height(36)
            .onClick(() => this.doClean())
          Button('List')
            .fontSize(14).width(70).height(36)
            .onClick(() => this.doList())
        }.margin({ bottom: 6 })

        Row() {
          Button('Count')
            .fontSize(14).width(70).height(36)
            .onClick(() => this.doCountFiles())
          Button('Large Save')
            .fontSize(14).width(90).height(36)
            .enabled(!this.saving)
            .onClick(() => this.doCreateLargeSave())
        }.margin({ bottom: 8 })

        Row() {
          Button('Run Tests')
            .fontSize(14).width(120).height(36)
            .enabled(!this.runningTests && this.pixelMap !== null)
            .onClick(() => this.doRunTests())
        }.margin({ bottom: 12 })

        Divider().margin({ bottom: 10 })

        if (this.imageInfoText.length > 0) {
          Text('Info: ' + this.imageInfoText)
            .fontSize(12).fontColor('#4CAF50').maxLines(3)
            .width('90%').margin({ bottom: 8 })
        }

        if (this.fileCount > 0) {
          Text('Files: ' + this.fileCount + ' Total: ' + this.totalSize)
            .fontSize(12).fontColor('#2196F3')
            .width('90%').margin({ bottom: 8 })
        }

        if (this.testResults.length > 0) {
          Text('-- Test Results --')
            .fontSize(13).fontWeight(FontWeight.Medium)
            .margin({ bottom: 4 })

          List() {
            ForEach(this.testResults, (r: TestResult) => {
              ListItem() {
                Row() {
                  Text(r.testName).fontSize(11).width(90)
                  Text(r.category).fontSize(10).fontColor('#999').width(60)
                  Text(r.passed ? 'PASS' : 'FAIL')
                    .fontSize(11).fontColor(r.passed ? '#4CAF50' : '#F44336').width(40)
                  Text(r.durationMs + 'ms').fontSize(10).fontColor('#999').width(50)
                  Text(r.message).fontSize(10).fontColor('#666').maxLines(1).layoutWeight(1)
                }.width('100%').padding({ left: 4, right: 4 })
              }
            })
          }
          .width('90%').height(180).margin({ bottom: 8 })
        }

        if (this.fileDetailList.length > 0) {
          Text('-- File Details --')
            .fontSize(13).fontWeight(FontWeight.Medium)
            .margin({ bottom: 4 })

          List() {
            ForEach(this.fileDetailList, (d: FileDetail) => {
              ListItem() {
                Row() {
                  Text(d.name).fontSize(11).width(100)
                  Text(formatFileSize(d.size)).fontSize(10).fontColor('#999').width(60)
                  Text(String(d.exists)).fontSize(10).width(40)
                }.width('100%').padding({ left: 4, right: 4 })
              }
            })
          }
          .width('90%').height(100).margin({ bottom: 8 })
        }

        if (this.logList.length > 0) {
          Text('-- Operation Log --')
            .fontSize(13).fontWeight(FontWeight.Medium)
            .margin({ bottom: 4 })

          List() {
            ForEach(this.logList, (log: OperationLog) => {
              ListItem() {
                Row() {
                  Text(log.operation).fontSize(11).width(70)
                  Text(log.timestamp).fontSize(10).fontColor('#999').width(110)
                  Text(log.success ? 'OK' : 'FAIL')
                    .fontSize(11).fontColor(log.success ? '#4CAF50' : '#F44336').width(30)
                  Text(log.detail).fontSize(10).fontColor('#666').maxLines(1).layoutWeight(1)
                }.width('100%').padding({ left: 4, right: 4 })
              }
            })
          }
          .width('90%').height(120).margin({ bottom: 12 })
        }

        Text(this.resultMsg)
          .fontSize(12).fontColor('#333').maxLines(10)
          .width('90%').padding(8)
          .backgroundColor('#F5F5F5').borderRadius(6)
      }
      .width('100%')
      .padding({ left: 16, right: 16 })
    }
    .width('100%')
    .height('100%')
  }
}