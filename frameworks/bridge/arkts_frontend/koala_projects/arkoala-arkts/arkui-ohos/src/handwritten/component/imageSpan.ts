import { InteropNativeModule, RuntimeType } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani";
import { PixelMap } from "#external";
import { ColorFilter, ResourceStr } from "./units";
import { Serializer } from "./peers/Serializer";
import { Resource } from "global.resource";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";

function hookSetImageSpanOptions(peer: ArkImageSpanPeer, value: ResourceStr | PixelMap): void {
    const thisSerializer : Serializer = Serializer.hold()
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if (TypeChecker.isPixelMap(value, false, false)) {
        const value_1  = value as PixelMap
        ArkUIAniModule._ImageSpan_Set_PixelMap(peer.getPeerPtr(), value_1)
        thisSerializer.release()
        return
    }
    if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
        thisSerializer.writeInt8(0 as int32)
        const value_0  = value as ResourceStr
        let value_0_type : int32 = RuntimeType.UNDEFINED
        value_0_type = runtimeType(value_0)
        if (RuntimeType.STRING == value_0_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0_0  = value_0 as string
            thisSerializer.writeString(value_0_0)
        }
        else if (RuntimeType.OBJECT == value_0_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_0_1  = value_0 as Resource
            thisSerializer.writeResource(value_0_1)
        }
    }
    ArkUIGeneratedNativeModule._ImageSpanInterface_setImageSpanOptions(peer.getPeerPtr(), thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()
}

function hookSetAlt(peer: ArkImageSpanPeer, value: PixelMap | undefined): void {
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        if (TypeChecker.isPixelMap(value, false, false)) {
            const value_value  = value as PixelMap
            ArkUIAniModule._ImageSpan_SetAlt_PixelMap(peer.getPeerPtr(), value_value)
            return
        }
    }
}