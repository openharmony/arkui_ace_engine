import { RuntimeType } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani";
import { PixelMap } from "#external";
import { ColorFilter, ResourceStr } from "./units";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";

function hookSetImageSpanOptions(imageSpanComponent: ArkImageSpanComponent, value: ResourceStr | PixelMap): void {
    if (TypeChecker.isPixelMap(value, false, false)) {
        const value_1  = value as PixelMap
        ArkUIAniModule._ImageSpan_Set_PixelMap(imageSpanComponent.getPeer().getPeerPtr(), value_1)
        return
    }
    imageSpanComponent.getPeer()?.setImageSpanOptionsAttribute(value)
}

function hookSetAlt(imageSpanComponent: ArkImageSpanComponent, value: PixelMap | undefined): void {
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        if (TypeChecker.isPixelMap(value, false, false)) {
            const value_value  = value as PixelMap
            ArkUIAniModule._ImageSpan_SetAlt_PixelMap(imageSpanComponent.getPeer().getPeerPtr(), value_value)
            return
        }
    }
}

function hookSetColorFilter(component: ArkImageSpanComponent,
                            value: ColorFilter | drawing.ColorFilter | undefined): void {
    if (value !== undefined && value instanceof drawing.ColorFilter) {
        const value_casted  = value as drawing.ColorFilter
        ArkUIAniModule._ImageSpan_Set_DrawingColorFilter(component.getPeer().getPeerPtr(), value_casted)
        return
    }
    component.getPeer()?.colorFilterAttribute(value)
}
