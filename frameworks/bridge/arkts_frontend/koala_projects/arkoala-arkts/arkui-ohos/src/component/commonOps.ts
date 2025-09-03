import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { runtimeType, RuntimeType, KPointer, toPeerPtr, SerializerBase } from "@koalaui/interop"
import { int64, int32 } from "@koalaui/common"
import { BlendMode, BlendApplyType } from "./common"
import { Serializer } from "./peers/Serializer"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class commonMethodOps {
    public static VisualEffectHandWrittenImpl(node: KPointer, value: int64): void {
        const node_casted = node as (KPointer)
        const value_casted = value as (int64)
        commonMethodOps.VisualEffectHandWrittenImpl_serialize(node_casted, value_casted)
        return
    }
    public static BackgroundFilterHandWrittenImpl(node: KPointer, value: int64): void {
        const node_casted = node as (KPointer)
        const value_casted = value as (int64)
        commonMethodOps.BackgroundFilterHandWrittenImpl_serialize(node_casted, value_casted)
        return
    }
    public static ForegroundFilterHandWrittenImpl(node: KPointer, value: int64): void {
        const node_casted = node as (KPointer)
        const value_casted = value as (int64)
        commonMethodOps.ForegroundFilterHandWrittenImpl_serialize(node_casted, value_casted)
        return
    }
    public static CompositingFilterHandWrittenImpl(node: KPointer, value: int64): void {
        const node_casted = node as (KPointer)
        const value_casted = value as (int64)
        commonMethodOps.CompositingFilterHandWrittenImpl_serialize(node_casted, value_casted)
        return
    }
    public static AdvancedBlendModeObjectImpl(node: KPointer, effect: int64, type?: BlendApplyType): void {
        const node_casted = node as (KPointer)
        const effect_casted = effect as (int64)
        const type_casted = type as (BlendApplyType | undefined)
        commonMethodOps.AdvancedBlendModeObjectImpl_serialize(node_casted, effect_casted, type_casted)
        return
    }
    public static AdvancedBlendModeEnumImpl(node: KPointer, effect?: BlendMode, type?: BlendApplyType): void {
        const node_casted = node as (KPointer)
        const effect_casted = effect as (BlendMode | undefined)
        const type_casted = type as (BlendApplyType | undefined)
        commonMethodOps.AdvancedBlendModeEnumImpl_serialize(node_casted, effect_casted, type_casted)
        return
    }
    private static VisualEffectHandWrittenImpl_serialize(node: KPointer, value: int64): void {
        ArkUIGeneratedNativeModule._commonMethodOps_VisualEffectHandWrittenImpl(node, value)
    }
    private static BackgroundFilterHandWrittenImpl_serialize(node: KPointer, value: int64): void {
        ArkUIGeneratedNativeModule._commonMethodOps_BackgroundFilterHandWrittenImpl(node, value)
    }
    private static ForegroundFilterHandWrittenImpl_serialize(node: KPointer, value: int64): void {
        ArkUIGeneratedNativeModule._commonMethodOps_ForegroundFilterHandWrittenImpl(node, value)
    }
    private static CompositingFilterHandWrittenImpl_serialize(node: KPointer, value: int64): void {
        ArkUIGeneratedNativeModule._commonMethodOps_CompositingFilterHandWrittenImpl(node, value)
    }
    private static AdvancedBlendModeObjectImpl_serialize(node: KPointer, effect: int64, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(type_value.valueOf())
        }
        ArkUIGeneratedNativeModule._commonMethodOps_AdvancedBlendModeObjectImpl(node, effect, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    
    private static AdvancedBlendModeEnumImpl_serialize(node: KPointer, effect?: BlendMode, type?: BlendApplyType): void {
        const thisSerializer : Serializer = Serializer.hold()
        let effect_type : int32 = RuntimeType.UNDEFINED
        effect_type = runtimeType(effect)
        thisSerializer.writeInt8(effect_type)
        if ((RuntimeType.UNDEFINED) != (effect_type)) {
            const effect_value  = (effect as BlendMode)
            thisSerializer.writeInt32(effect_value.valueOf())
        }
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = (type as BlendApplyType)
            thisSerializer.writeInt32(type_value.valueOf())
        }
        ArkUIGeneratedNativeModule._commonMethodOps_AdvancedBlendModeEnumImpl(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}