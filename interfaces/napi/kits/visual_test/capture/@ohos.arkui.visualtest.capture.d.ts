/**
 * ArkUI Render Test — capture module.
 * Frame capture from the render pipeline, touch injection,
 * render events, and environment queries.
 *
 * Usage:  import capture from '@ohos.arkui.visualtest.capture';
 */

declare namespace capture {
    /** A captured frame: raw RGBA pixel data plus dimensions. */
    interface Frame {
        readonly data: ArrayBuffer;
        readonly width: number;
        readonly height: number;
    }

    /** Frame dimensions in pixels. */
    interface ScreenSize {
        readonly width: number;
        readonly height: number;
    }

    /** Callback type for event subscriptions. */
    type FrameCallback = (frame: Frame) => void;

    /**
     * Subscription token.
     * Controls the lifetime of an event listener.
     */
    interface Token {
        /** Which event this token subscribes to. */
        readonly event: string;
        /** Whether the subscription is still active. */
        readonly active: boolean;
        /** Remove this subscription. Idempotent. */
        unsubscribe(): void;
    }

    /** Environment information. */
    interface Env {
        /** True when running under any previewer (GUI or headless). */
        readonly isPreviewer: boolean;
        /** True when running under the headless previewer specifically. */
        readonly isHeadless: boolean;
        /** Current frame dimensions in pixels. */
        readonly screenSize: ScreenSize;
    }

    // ---- Frame capture ----

    /**
     * Capture a single frame. Convenience: requestFrame + awaitFrame + collectFrame.
     * Returns Promise<Frame>. Rejects on timeout.
     */
    function captureFrame(timeoutMs?: number): Promise<Frame>;

    /**
     * Request a frame capture from the render pipeline.
     * Returns a request identifier for use with awaitFrame and collectFrame.
     */
    function requestFrame(): number;

    /**
     * Wait for the requested frame to become ready.
     * Returns true when the frame is captured, false on timeout.
     */
    function awaitFrame(requestId: number, timeoutMs: number): boolean;

    /**
     * Retrieve a captured frame by its request identifier.
     * Call only after awaitFrame returned true.
     * The frame is removed from internal storage on collect.
     */
    function collectFrame(requestId: number): Frame;

    /**
     * Discard a number of frames without processing them.
     * Useful for skipping initial render noise before actual capture.
     */
    function skipFrames(count: number): void;

    /**
     * Wait until the render pipeline is idle (no dirty nodes, no animations)
     * or timeoutMs elapses. Returns true if idle, false on timeout.
     *
     * @deprecated Use awaitIdle() instead.
     */
    function waitForIdle(timeoutMs: number): boolean;

    // ---- Events ----

    /** Subscribe to every rendered frame. */
    function onFrame(cb: FrameCallback): Token;

    /** Subscribe to the next frame only. Auto-unsubscribes after first call. */
    function onceFrame(cb: FrameCallback): Token;

    /** Wait until the render pipeline is idle. Resolves on idle, rejects on timeout. */
    function awaitIdle(timeoutMs?: number): Promise<void>;

    /**
     * Subscribe to render-idle events.
     * Idle means the frame hash is stable for 3 consecutive frames.
     * Fires after animations and layout settle, but with lower timing precision
     * than onScrollEnd.
     */
    function onIdle(cb: FrameCallback): Token;

    /** Subscribe to the next idle event only. */
    function onceIdle(cb: FrameCallback): Token;

    /**
     * Subscribe to scroll-end events.
     * Fires at the exact moment the engine finishes scrolling.
     * More precise than onIdle for scroll-specific tests.
     */
    function onScrollEnd(cb: FrameCallback): Token;

    /** Subscribe to the next scroll-end event only. */
    function onceScrollEnd(cb: FrameCallback): Token;

    /** Subscribe to animation-end events. Fires when animation completes. */
    function onAnimationEnd(cb: FrameCallback): Token;

    /** Subscribe to the next animation-end event only. */
    function onceAnimationEnd(cb: FrameCallback): Token;

    /** Subscribe to errors from the render pipeline. */
    function onError(cb: FrameCallback): Token;

    /** Subscribe to the next error event only. */
    function onceError(cb: FrameCallback): Token;

    /**
     * Unsubscribe all listeners.
     * Without argument — all events. With event — only that event type.
     *
     * After abort() all existing Token objects become invalid.
     * Their `active` property is no longer reliable.
     */
    function abort(event?: string): void;

    // ---- Touch injection ----

    /**
     * Inject a touch-press at viewport coordinates (x, y).
     * Synchronous. Begins a touch sequence.
     */
    function touchDown(x: number, y: number): void;

    /**
     * Inject a touch-move to viewport coordinates (x, y).
     * Synchronous. Call only after touchDown.
     */
    function touchMove(x: number, y: number): void;

    /**
     * Inject a touch-release at viewport coordinates (x, y).
     * Synchronous. Ends a touch sequence.
     */
    function touchUp(x: number, y: number): void;

    /**
     * Swipe from (x1,y1) to (x2,y2) over durationMs (default 300).
     * Returns Promise that resolves after the gesture completes.
     */
    function swipe(x1: number, y1: number, x2: number, y2: number, durationMs?: number): Promise<void>;

    /**
     * Long press at (x,y) for durationMs (default 500).
     * Returns Promise that resolves after the gesture completes.
     */
    function longPress(x: number, y: number, durationMs?: number): Promise<void>;

    // ---- Environment ----

    /** Environment information: isPreviewer, isHeadless, screenSize. */
    const env: Env;

    /** True when running under any previewer (GUI or headless). */
    function isPreviewer(): boolean;

    /** True when running under the headless previewer specifically. */
    function isHeadless(): boolean;

    /** Current frame dimensions in pixels. */
    function getScreenSize(): ScreenSize;

    // ---- File I/O ----

    /**
     * Write binary data to a file.
     * Creates parent directories recursively.
     * Returns true on success.
     */
    function writeFile(path: string, data: ArrayBuffer): boolean;

    // ---- Lifecycle ----

    /**
     * Signal the headless host to exit cleanly.
     * Previewer only — not available on device.
     * Check env.isPreviewer before calling.
     */
    function exit(): void;

    /**
     * Set the output directory for captures and diffs.
     * Called by the previewer host before tests start.
     */
    function setOutputDir(dir: string): void;

    /**
     * Set the HAP directory for golden image lookup.
     * Called on device to locate extracted rawfile resources.
     */
    function setHapDir(dir: string): void;
}

export default capture;
