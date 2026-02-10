import { CustomSpanNative } from './idlize'
import { CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo } from './styledString'
import { DrawContext as arkui_Graphics_DrawContext } from 'arkui.Graphics'

export abstract class CustomSpan {
    public readonly nativeObj: CustomSpanNative
    constructor() {
        this.nativeObj = new CustomSpanNative()
    }

    // Improve to abstract
    onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics
        { return {width:0} as CustomSpanMetrics };
    onDraw(context: arkui_Graphics_DrawContext, drawInfo: CustomSpanDrawInfo): void
        {}
    invalidate(): void {
        this.nativeObj.invalidate()
    }
}
