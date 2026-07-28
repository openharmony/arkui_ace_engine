/**
 * ArkUI Render Test — compare module.
 * SSIM comparison, PNG codec, CIELAB diff rendering.
 *
 * Usage:  import compare from '@ohos.arkui.visualtest.compare';
 */

declare namespace compare {
    /** An RGBA image: raw pixel data plus dimensions. */
    interface Image {
        readonly data: ArrayBuffer;
        readonly width: number;
        readonly height: number;
    }

    /** Result of an SSIM comparison. */
    interface DiffResult {
        readonly pass: boolean;
        readonly score: number;
        /** null, "SIZE_MISMATCH", or "GOLDEN_NOT_FOUND". */
        readonly error: string | null;
    }

    /**
     * Compare two RGBA images using SSIM (8x8 sliding window, luminance channel).
     *
     * @param threshold SSIM threshold, default 0.95.  score >= threshold → pass.
     */
    function compare(
        actual: ArrayBuffer, actualWidth: number, actualHeight: number,
        golden: ArrayBuffer, goldenWidth: number, goldenHeight: number,
        threshold?: number
    ): DiffResult;

    /**
     * Decode a PNG from a memory buffer.
     * Golden files can be loaded via resourceManager.getRawFileContent()
     * and passed directly as an ArrayBuffer.
     */
    function decodePNG(data: ArrayBuffer): Image;

    /** Decode a PNG file from the filesystem. Returns an Image { data, width, height }. */
    function decodePNGFile(path: string): Image;

    /** Encode an RGBA image to PNG in memory. Returns the PNG bytes. */
    function encodePNG(data: ArrayBuffer, width: number, height: number): ArrayBuffer;

    /** Write an RGBA image to a PNG file on disk. */
    function writePNG(data: ArrayBuffer, width: number, height: number, path: string): void;

    /**
     * Write a CIELAB delta-E diff heat map.
     * Red pixels indicate a perceptual difference (distance > 0.5).
     */
    function writeDiff(
        actual: ArrayBuffer, actualWidth: number, actualHeight: number,
        golden: ArrayBuffer, goldenWidth: number, goldenHeight: number,
        path: string
    ): void;

    /** Write a JSON string to a file. Used for manifest.json output. */
    function writeManifest(json: string, path: string): void;
}

export default compare;
