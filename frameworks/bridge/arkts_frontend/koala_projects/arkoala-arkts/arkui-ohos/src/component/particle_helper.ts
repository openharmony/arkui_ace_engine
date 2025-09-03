import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"
import { unsafeCast, int32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { ICurve } from "./common"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { VP, Dimension, ResourceStr, ResourceColor } from "./units"
import { Resource } from "global.resource"
import { Color, Curve, ImageFit } from "./enums"
import { SizeT, PositionT, LengthMetrics } from "../Graphics"
import { ParticleUpdater, ParticleColorOptions, VelocityOptions, EmitterParticleOptions, ParticleEmitterShape, DistributionType } from "./particle"
import { DisturbanceFieldShape, PointParticleParameters, ImageParticleParameters } from "./particle"

// inner class
export interface SizeNumberInner {
    width: number;
    height: number;
}
export interface PositionNumberInner {
    x: number;
    y: number;
}
export interface PositionLengthMetricsInner {
    x: LengthMetrics;
    y: LengthMetrics;
}
export interface ParticlePropertyAnimationNumberInner {
    from: number;
    to: number;
    startMillis: number;
    endMillis: number;
    curve?: Curve | ICurve;
}
export interface ParticlePropertyAnimationColorInner {
    from: ResourceColor;
    to: ResourceColor;
    startMillis: number;
    endMillis: number;
    curve?: Curve | ICurve;
}
export type ParticlePropertyUpdaterConfigsInner = [ number, number ] | Array<ParticlePropertyAnimationNumberInner> | undefined;
export interface ParticleUpdaterOptionsInner {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigsInner;
}
export interface ParticlePropertyOptionsInner {
    range: [ number, number ];
    updater?: ParticleUpdaterOptionsInner;
}
export interface ParticleColorUpdaterOptionsInner {
    type: ParticleUpdater;
    config: ParticleColorPropertyUpdaterConfigsInner;
}
export type ParticleColorPropertyUpdaterConfigsInner = ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined;
export interface AccelerationOptionsInner {
    speed?: ParticlePropertyOptionsInner;
    angle?: ParticlePropertyOptionsInner;
}
export interface ParticleOptionsInner {
    emitter: EmitterOptionsInner;
    color?: ParticleColorPropertyOptionsInner;
    opacity?: ParticlePropertyOptionsInner;
    scale?: ParticlePropertyOptionsInner;
    velocity?: VelocityOptions;
    acceleration?: AccelerationOptionsInner;
    spin?: ParticlePropertyOptionsInner;
}
export interface ParticleAnnulusRegionInner {
    center?: PositionLengthMetricsInner;
    outerRadius: LengthMetrics;
    innerRadius: LengthMetrics;
    startAngle?: number;
    endAngle?: number;
}
export interface EmitterPropertyInner {
    index: number;
    emitRate?: number;
    position?: PositionNumberInner;
    size?: SizeNumberInner;
    annulusRegion?: ParticleAnnulusRegionInner;
}
export interface EmitterOptionsInner {
    particle: EmitterParticleOptions;
    emitRate?: number;
    shape?: ParticleEmitterShape;
    position?: [ Dimension, Dimension ];
    size?: [ Dimension, Dimension ];
    annulusRegion?: ParticleAnnulusRegionInner;
}
export interface ParticleColorPropertyOptionsInner {
    range: [ ResourceColor, ResourceColor ];
    distributionType?: DistributionType;
    updater?: ParticleColorUpdaterOptionsInner;
}
export interface ParticlesInner {
    particles: Array<ParticleOptionsInner>;
}
export interface DisturbanceFieldOptionsInner {
    strength?: number;
    shape?: DisturbanceFieldShape;
    size?: SizeNumberInner;
    position?: PositionNumberInner;
    feather?: number;
    noiseScale?: number;
    noiseFrequency?: number;
    noiseAmplitude?: number;
}

export class ParticleHelper {
    public static SetDisturbanceFields(node: KPointer, disturbanceFields: Array<DisturbanceFieldOptionsInner> | undefined): void {
        const node_casted = node as (KPointer)
        const disturbanceFields_casted = disturbanceFields as (Array<DisturbanceFieldOptionsInner> | undefined)
        ParticleHelper.SetDisturbanceFields_serialize(node_casted, disturbanceFields_casted)
        return
    }
    public static SetEmitterProperty(node: KPointer, emitter: Array<EmitterPropertyInner> | undefined): void {
        const node_casted = node as (KPointer)
        const emitter_casted = emitter as (Array<EmitterPropertyInner> | undefined)
        ParticleHelper.SetEmitterProperty_serialize(node_casted, emitter_casted)
        return
    }
    public static ParticleConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ParticleHelper.ParticleConstruct_serialize(id_casted, flags_casted)
    }
    public static SetParticleOptions(node: KPointer, particles: ParticlesInner): void {
        const node_casted = node as (KPointer)
        const particles_casted = particles as (ParticlesInner)
        ParticleHelper.SetParticleOptions_serialize(node_casted, particles_casted)
        return
    }
    private static SetDisturbanceFields_serialize(node: KPointer, disturbanceFields: Array<DisturbanceFieldOptionsInner> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let disturbanceFields_type : int32 = RuntimeType.UNDEFINED
        disturbanceFields_type = runtimeType(disturbanceFields)
        thisSerializer.writeInt8(disturbanceFields_type)
        if ((RuntimeType.UNDEFINED) != (disturbanceFields_type)) {
            const disturbanceFields_value  = disturbanceFields!
            thisSerializer.writeInt32(disturbanceFields_value.length as int32)
            for (let i = 0; i < disturbanceFields_value.length; i++) {
                const disturbanceFields_value_element : DisturbanceFieldOptionsInner = disturbanceFields_value[i]
                DisturbanceFieldOptionsInner_serializer.write(thisSerializer, disturbanceFields_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetDisturbanceFields(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetEmitterProperty_serialize(node: KPointer, emitter: Array<EmitterPropertyInner> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let emitter_type : int32 = RuntimeType.UNDEFINED
        emitter_type = runtimeType(emitter)
        thisSerializer.writeInt8(emitter_type)
        if ((RuntimeType.UNDEFINED) != (emitter_type)) {
            const emitter_value  = emitter!
            thisSerializer.writeInt32(emitter_value.length as int32)
            for (let i = 0; i < emitter_value.length; i++) {
                const emitter_value_element : EmitterPropertyInner = emitter_value[i]
                EmitterPropertyInner_serializer.write(thisSerializer, emitter_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetEmitterProperty(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static ParticleConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ParticleHelper_ParticleConstruct(id, flags)
        return retval
    }
    private static SetParticleOptions_serialize(node: KPointer, particles: ParticlesInner): void {
        const thisSerializer : Serializer = Serializer.hold()
        ParticlesInner_serializer.write(thisSerializer, particles)
        ArkUIGeneratedNativeModule._ParticleHelper_SetParticleOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export class VelocityOptions_serializer {
    public static write(buffer: Serializer, value: VelocityOptions): void {
        let valueSerializer: Serializer = buffer
        const value_speed = value.speed
        const value_speed_0 = value_speed[0]
        valueSerializer.writeNumber(value_speed_0)
        const value_speed_1 = value_speed[1]
        valueSerializer.writeNumber(value_speed_1)
        const value_angle = value.angle
        const value_angle_0 = value_angle[0]
        valueSerializer.writeNumber(value_angle_0)
        const value_angle_1 = value_angle[1]
        valueSerializer.writeNumber(value_angle_1)
    }
}

export class EmitterPropertyInner_serializer {
    public static write(buffer: Serializer, value: EmitterPropertyInner): void {
        let valueSerializer : Serializer = buffer
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
        const value_emitRate  = value.emitRate
        let value_emitRate_type : int32 = RuntimeType.UNDEFINED
        value_emitRate_type = runtimeType(value_emitRate)
        valueSerializer.writeInt8(value_emitRate_type)
        if ((RuntimeType.UNDEFINED) != (value_emitRate_type)) {
            const value_emitRate_value  = value_emitRate!
            valueSerializer.writeNumber(value_emitRate_value)
        }
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8(value_position_type)
        if ((RuntimeType.UNDEFINED) != (value_position_type)) {
            const value_position_value  = value_position!
            PositionNumberInner_serializer.write(valueSerializer, value_position_value)
        }
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8(value_size_type)
        if ((RuntimeType.UNDEFINED) != (value_size_type)) {
            const value_size_value  = value_size!
            SizeNumberInner_serializer.write(valueSerializer, value_size_value)
        }
        const value_annulusRegion  = value.annulusRegion
        let value_annulusRegion_type : int32 = RuntimeType.UNDEFINED
        value_annulusRegion_type = runtimeType(value_annulusRegion)
        valueSerializer.writeInt8(value_annulusRegion_type)
        if ((RuntimeType.UNDEFINED) != (value_annulusRegion_type)) {
            const value_annulusRegion_value  = value_annulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, value_annulusRegion_value)
        }
    }
}

export class ParticleColorOptions_serializer {
    public static write(buffer: Serializer, value: ParticleColorOptions): void {
        let valueSerializer: Serializer = buffer
        const value_r = value.r
        const value_r_0 = value_r[0]
        valueSerializer.writeNumber(value_r_0)
        const value_r_1 = value_r[1]
        valueSerializer.writeNumber(value_r_1)
        const value_g = value.g
        const value_g_0 = value_g[0]
        valueSerializer.writeNumber(value_g_0)
        const value_g_1 = value_g[1]
        valueSerializer.writeNumber(value_g_1)
        const value_b = value.b
        const value_b_0 = value_b[0]
        valueSerializer.writeNumber(value_b_0)
        const value_b_1 = value_b[1]
        valueSerializer.writeNumber(value_b_1)
        const value_a = value.a
        const value_a_0 = value_a[0]
        valueSerializer.writeNumber(value_a_0)
        const value_a_1 = value_a[1]
        valueSerializer.writeNumber(value_a_1)
    }
}

export class ParticlePropertyAnimationColorInner_serializer {
    public static write(buffer: Serializer, value: ParticlePropertyAnimationColorInner): void {
        let valueSerializer : Serializer = buffer
        const value_from  = value.from
        let value_from_type : int32 = RuntimeType.UNDEFINED
        value_from_type = runtimeType(value_from)
        if (TypeChecker.isColor(value_from)) {
            valueSerializer.writeInt8(0)
            const value_from_0  = value_from as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_from_0))
        }
        else if (RuntimeType.NUMBER == value_from_type) {
            valueSerializer.writeInt8(1)
            const value_from_1  = value_from as number
            valueSerializer.writeNumber(value_from_1)
        }
        else if (RuntimeType.STRING == value_from_type) {
            valueSerializer.writeInt8(2)
            const value_from_2  = value_from as string
            valueSerializer.writeString(value_from_2)
        }
        else if (RuntimeType.OBJECT == value_from_type) {
            valueSerializer.writeInt8(3)
            const value_from_3  = value_from as Resource
            valueSerializer.writeResource(value_from_3)
        }
        const value_to  = value.to
        let value_to_type : int32 = RuntimeType.UNDEFINED
        value_to_type = runtimeType(value_to)
        if (TypeChecker.isColor(value_to)) {
            valueSerializer.writeInt8(0)
            const value_to_0  = value_to as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_to_0))
        }
        else if (RuntimeType.NUMBER == value_to_type) {
            valueSerializer.writeInt8(1)
            const value_to_1  = value_to as number
            valueSerializer.writeNumber(value_to_1)
        }
        else if (RuntimeType.STRING == value_to_type) {
            valueSerializer.writeInt8(2)
            const value_to_2  = value_to as string
            valueSerializer.writeString(value_to_2)
        }
        else if (RuntimeType.OBJECT == value_to_type) {
            valueSerializer.writeInt8(3)
            const value_to_3  = value_to as Resource
            valueSerializer.writeResource(value_to_3)
        }
        const value_startMillis  = value.startMillis
        valueSerializer.writeNumber(value_startMillis)
        const value_endMillis  = value.endMillis
        valueSerializer.writeNumber(value_endMillis)
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        valueSerializer.writeInt8(value_curve_type)
        if ((RuntimeType.UNDEFINED) != (value_curve_type)) {
            const value_curve_value  = value_curve!
            let value_curve_value_type : int32 = RuntimeType.UNDEFINED
            value_curve_value_type = runtimeType(value_curve_value)
            if (TypeChecker.isCurve(value_curve_value)) {
                valueSerializer.writeInt8(0)
                const value_curve_value_0  = value_curve_value as Curve
                valueSerializer.writeInt32(value_curve_value_0.valueOf())
            }
            else if (RuntimeType.OBJECT == value_curve_value_type) {
                valueSerializer.writeInt8(1)
                const value_curve_value_1  = value_curve_value as ICurve
                valueSerializer.writeICurve(value_curve_value_1)
            }
        }
    }
}
export class ParticlePropertyAnimationNumberInner_serializer {
    public static write(buffer: Serializer, value: ParticlePropertyAnimationNumberInner): void {
        let valueSerializer : Serializer = buffer
        const value_from  = value.from
        valueSerializer.writeNumber(value_from)
        const value_to  = value.to
        valueSerializer.writeNumber(value_to)
        const value_startMillis  = value.startMillis
        valueSerializer.writeNumber(value_startMillis)
        const value_endMillis  = value.endMillis
        valueSerializer.writeNumber(value_endMillis)
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        valueSerializer.writeInt8(value_curve_type)
        if ((RuntimeType.UNDEFINED) != (value_curve_type)) {
            const value_curve_value  = value_curve!
            let value_curve_value_type : int32 = RuntimeType.UNDEFINED
            value_curve_value_type = runtimeType(value_curve_value)
            if (TypeChecker.isCurve(value_curve_value)) {
                valueSerializer.writeInt8(0)
                const value_curve_value_0  = value_curve_value as Curve
                valueSerializer.writeInt32(value_curve_value_0.valueOf())
            }
            else if (RuntimeType.OBJECT == value_curve_value_type) {
                valueSerializer.writeInt8(1)
                const value_curve_value_1  = value_curve_value as ICurve
                valueSerializer.writeICurve(value_curve_value_1)
            }
        }
    }
}

export class ParticlesInner_serializer {
    public static write(buffer: Serializer, value: ParticlesInner): void {
        let valueSerializer : Serializer = buffer
        const value_particles  = value.particles
        valueSerializer.writeInt32(value_particles.length as int32)
        for (let i = 0; i < value_particles.length; i++) {
            const value_particles_element : ParticleOptionsInner = value_particles[i]
            ParticleOptionsInner_serializer.write(valueSerializer, value_particles_element)
        }
    }
}

export class PointParticleParameters_serializer {
    public static write(buffer: Serializer, value: PointParticleParameters): void {
        let valueSerializer: Serializer = buffer
        const value_radius = value.radius
        let value_radius_type: int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        if (RuntimeType.STRING == value_radius_type) {
            valueSerializer.writeInt8(0)
            const value_radius_0 = value_radius as string
            valueSerializer.writeString(value_radius_0)
        }
        else if (RuntimeType.NUMBER == value_radius_type) {
            valueSerializer.writeInt8(1)
            const value_radius_1 = value_radius as number
            valueSerializer.writeNumber(value_radius_1)
        }
    }
}
export class ParticleUpdaterOptionsInner_serializer {
    public static write(buffer: Serializer, value: ParticleUpdaterOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(value_type.getOrdinal())
        const value_config  = value.config
        let value_config_type : int32 = RuntimeType.UNDEFINED
        value_config_type = runtimeType(value_config)
        valueSerializer.writeInt8(value_config_type)
        if ((RuntimeType.UNDEFINED) != (value_config_type)) {
            const value_config_value  = value_config!
            let value_config_value_type : int32 = RuntimeType.UNDEFINED
            value_config_value_type = runtimeType(value_config_value)
            if (((RuntimeType.OBJECT) == (value_config_value_type)) && (value_config_value instanceof Tuple)) {
                valueSerializer.writeInt8(0)
                const value_config_value_0  = value_config_value as [ number, number ]
                const value_config_value_0_0  = value_config_value_0[0]
                valueSerializer.writeNumber(value_config_value_0_0)
                const value_config_value_0_1  = value_config_value_0[1]
                valueSerializer.writeNumber(value_config_value_0_1)
            }
            else if (((RuntimeType.OBJECT) == (value_config_value_type)) && (TypeChecker.isArray_ParticlePropertyAnimationNumberInner(value_config_value))) {
                valueSerializer.writeInt8(1)
                const value_config_value_1  = value_config_value as Array<ParticlePropertyAnimationNumberInner>
                valueSerializer.writeInt32(value_config_value_1.length as int32)
                for (let i = 0; i < value_config_value_1.length; i++) {
                    const value_config_value_1_element : ParticlePropertyAnimationNumberInner = value_config_value_1[i]
                    ParticlePropertyAnimationNumberInner_serializer.write(valueSerializer, value_config_value_1_element)
                }
            }
        }
    }
}
export class PositionNumberInner_serializer {
    public static write(buffer: Serializer, value: PositionNumberInner): void {
        let valueSerializer : Serializer = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
    }
}
export class PositionLengthMetricsInner_serializer {
    public static write(buffer: Serializer, value: PositionLengthMetricsInner): void {
        let valueSerializer : Serializer = buffer
        const value_x  = value.x
        valueSerializer.writeLengthMetrics(value_x)
        const value_y  = value.y
        valueSerializer.writeLengthMetrics(value_y)
    }
}
export class SizeNumberInner_serializer {
    public static write(buffer: Serializer, value: SizeNumberInner): void {
        let valueSerializer : Serializer = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
    }
}


export class ImageParticleParameters_serializer {
    public static write(buffer: Serializer, value: ImageParticleParameters): void {
        let valueSerializer: Serializer = buffer
        const value_src = value.src
        let value_src_type: int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        if (RuntimeType.STRING == value_src_type) {
            valueSerializer.writeInt8(0)
            const value_src_0 = value_src as string
            valueSerializer.writeString(value_src_0)
        }
        else if (RuntimeType.OBJECT == value_src_type) {
            valueSerializer.writeInt8(1)
            const value_src_1 = value_src as Resource
            valueSerializer.writeResource(value_src_1)
        }
        const value_size = value.size
        const value_size_0 = value_size[0]
        valueSerializer.writeLength(value_size_0);
        const value_size_1 = value_size[1]
        valueSerializer.writeLength(value_size_1);
        const value_objectFit = value.objectFit
        let value_objectFit_type: int32 = RuntimeType.UNDEFINED
        value_objectFit_type = runtimeType(value_objectFit)
        valueSerializer.writeInt8(value_objectFit_type)
        if ((RuntimeType.UNDEFINED) != (value_objectFit_type)) {
            const value_objectFit_value  = (value_objectFit as ImageFit)
            valueSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_objectFit_value))
        }
    }
}
export class ParticleAnnulusRegionInner_serializer {
    public static write(buffer: Serializer, value: ParticleAnnulusRegionInner): void {
        let valueSerializer : Serializer = buffer
        const value_center  = value.center
        let value_center_type : int32 = RuntimeType.UNDEFINED
        value_center_type = runtimeType(value_center)
        valueSerializer.writeInt8(value_center_type)
        if ((RuntimeType.UNDEFINED) != (value_center_type)) {
            const value_center_value  = value_center!
            PositionLengthMetricsInner_serializer.write(valueSerializer, value_center_value)
        }
        const value_outerRadius  = value.outerRadius
        valueSerializer.writeLengthMetrics(value_outerRadius)
        const value_innerRadius  = value.innerRadius
        valueSerializer.writeLengthMetrics(value_innerRadius)
        const value_startAngle  = value.startAngle
        let value_startAngle_type : int32 = RuntimeType.UNDEFINED
        value_startAngle_type = runtimeType(value_startAngle)
        valueSerializer.writeInt8(value_startAngle_type)
        if ((RuntimeType.UNDEFINED) != (value_startAngle_type)) {
            const value_startAngle_value  = value_startAngle!
            valueSerializer.writeNumber(value_startAngle_value)
        }
        const value_endAngle  = value.endAngle
        let value_endAngle_type : int32 = RuntimeType.UNDEFINED
        value_endAngle_type = runtimeType(value_endAngle)
        valueSerializer.writeInt8(value_endAngle_type)
        if ((RuntimeType.UNDEFINED) != (value_endAngle_type)) {
            const value_endAngle_value  = value_endAngle!
            valueSerializer.writeNumber(value_endAngle_value)
        }
    }
}
export class ParticleColorUpdaterOptionsInner_serializer {
    public static write(buffer: Serializer, value: ParticleColorUpdaterOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(value_type.getOrdinal())
        const value_config  = value.config
        let value_config_type : int32 = RuntimeType.UNDEFINED
        value_config_type = runtimeType(value_config)
        valueSerializer.writeInt8(value_config_type)
        if ((RuntimeType.UNDEFINED) != (value_config_type)) {
            const value_config_value  = value_config!
            let value_config_value_type : int32 = RuntimeType.UNDEFINED
            value_config_value_type = runtimeType(value_config_value)
            if (TypeChecker.isParticleColorOptions(value_config_value, false, false, false, false)) {
                valueSerializer.writeInt8(0)
                const value_config_value_0  = value_config_value as ParticleColorOptions
                ParticleColorOptions_serializer.write(valueSerializer, value_config_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_config_value_type)) && (TypeChecker.isArray_ParticlePropertyAnimationColorInner(value_config_value))) {
                valueSerializer.writeInt8(1)
                const value_config_value_1  = value_config_value as Array<ParticlePropertyAnimationColorInner>
                valueSerializer.writeInt32(value_config_value_1.length as int32)
                for (let i = 0; i < value_config_value_1.length; i++) {
                    const value_config_value_1_element : ParticlePropertyAnimationColorInner = value_config_value_1[i]
                    ParticlePropertyAnimationColorInner_serializer.write(valueSerializer, value_config_value_1_element)
                }
            }
        }
    }
}

export class ParticlePropertyOptionsInner_serializer {
    public static write(buffer: Serializer, value: ParticlePropertyOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_range  = value.range
        const value_range_0  = value_range[0]
        valueSerializer.writeNumber(value_range_0)
        const value_range_1  = value_range[1]
        valueSerializer.writeNumber(value_range_1)
        const value_updater  = value.updater
        let value_updater_type : int32 = RuntimeType.UNDEFINED
        value_updater_type = runtimeType(value_updater)
        valueSerializer.writeInt8(value_updater_type)
        if ((RuntimeType.UNDEFINED) != (value_updater_type)) {
            const value_updater_value  = value_updater!
            ParticleUpdaterOptionsInner_serializer.write(valueSerializer, value_updater_value)
        }
    }
}

export class AccelerationOptionsInner_serializer {
    public static write(buffer: Serializer, value: AccelerationOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_speed  = value.speed
        let value_speed_type : int32 = RuntimeType.UNDEFINED
        value_speed_type = runtimeType(value_speed)
        valueSerializer.writeInt8(value_speed_type)
        if ((RuntimeType.UNDEFINED) != (value_speed_type)) {
            const value_speed_value  = value_speed!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, value_speed_value)
        }
        const value_angle  = value.angle
        let value_angle_type : int32 = RuntimeType.UNDEFINED
        value_angle_type = runtimeType(value_angle)
        valueSerializer.writeInt8(value_angle_type)
        if ((RuntimeType.UNDEFINED) != (value_angle_type)) {
            const value_angle_value  = value_angle!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, value_angle_value)
        }
    }
}

export class EmitterParticleOptions_serializer {
    public static write(buffer: Serializer, value: EmitterParticleOptions): void {
        let valueSerializer: Serializer = buffer
        const value_type = value.type
        valueSerializer.writeInt32(value_type.getOrdinal())
        const value_config = value.config
        let value_config_type: int32 = RuntimeType.UNDEFINED
        value_config_type = runtimeType(value_config)
        if (((RuntimeType.OBJECT) == (value_config_type)) && ((value_config!.hasOwnProperty("radius")))) {
            valueSerializer.writeInt8(0)
            const value_config_0 = value_config as PointParticleParameters
            PointParticleParameters_serializer.write(valueSerializer, value_config_0)
        }
        else if (((RuntimeType.OBJECT) == (value_config_type)) && ((value_config!.hasOwnProperty("src")))) {
            valueSerializer.writeInt8(1)
            const value_config_1 = value_config as ImageParticleParameters
            ImageParticleParameters_serializer.write(valueSerializer, value_config_1)
        }
        const value_count = value.count
        valueSerializer.writeNumber(value_count)
        const value_lifetime = value.lifetime
        let value_lifetime_type: int32 = RuntimeType.UNDEFINED
        value_lifetime_type = runtimeType(value_lifetime)
        valueSerializer.writeInt8(value_lifetime_type)
        if ((RuntimeType.UNDEFINED) != (value_lifetime_type)) {
            const value_lifetime_value = value_lifetime!
            valueSerializer.writeNumber(value_lifetime_value)
        }
        const value_lifetimeRange = value.lifetimeRange
        let value_lifetimeRange_type: int32 = RuntimeType.UNDEFINED
        value_lifetimeRange_type = runtimeType(value_lifetimeRange)
        valueSerializer.writeInt8(value_lifetimeRange_type)
        if ((RuntimeType.UNDEFINED) != (value_lifetimeRange_type)) {
            const value_lifetimeRange_value = value_lifetimeRange!
            valueSerializer.writeNumber(value_lifetimeRange_value)
        }
    }
}
export class ParticleColorPropertyOptionsInner_serializer {
    public static write(buffer: Serializer, value: ParticleColorPropertyOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_range  = value.range
        const value_range_0  = value_range[0]
        let value_range_0_type : int32 = RuntimeType.UNDEFINED
        value_range_0_type = runtimeType(value_range_0)
        if (TypeChecker.isColor(value_range_0)) {
            valueSerializer.writeInt8(0)
            const value_range_0_0  = value_range_0 as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_range_0_0))
        }
        else if (RuntimeType.NUMBER == value_range_0_type) {
            valueSerializer.writeInt8(1)
            const value_range_0_1  = value_range_0 as number
            valueSerializer.writeNumber(value_range_0_1)
        }
        else if (RuntimeType.STRING == value_range_0_type) {
            valueSerializer.writeInt8(2)
            const value_range_0_2  = value_range_0 as string
            valueSerializer.writeString(value_range_0_2)
        }
        else if (RuntimeType.OBJECT == value_range_0_type) {
            valueSerializer.writeInt8(3)
            const value_range_0_3  = value_range_0 as Resource
            valueSerializer.writeResource(value_range_0_3)
        }
        const value_range_1  = value_range[1]
        let value_range_1_type : int32 = RuntimeType.UNDEFINED
        value_range_1_type = runtimeType(value_range_1)
        if (TypeChecker.isColor(value_range_1)) {
            valueSerializer.writeInt8(0)
            const value_range_1_0  = value_range_1 as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_range_1_0))
        }
        else if (RuntimeType.NUMBER == value_range_1_type) {
            valueSerializer.writeInt8(1)
            const value_range_1_1  = value_range_1 as number
            valueSerializer.writeNumber(value_range_1_1)
        }
        else if (RuntimeType.STRING == value_range_1_type) {
            valueSerializer.writeInt8(2)
            const value_range_1_2  = value_range_1 as string
            valueSerializer.writeString(value_range_1_2)
        }
        else if (RuntimeType.OBJECT == value_range_1_type) {
            valueSerializer.writeInt8(3)
            const value_range_1_3  = value_range_1 as Resource
            valueSerializer.writeResource(value_range_1_3)
        }
        const value_distributionType  = value.distributionType
        let value_distributionType_type : int32 = RuntimeType.UNDEFINED
        value_distributionType_type = runtimeType(value_distributionType)
        valueSerializer.writeInt8(value_distributionType_type)
        if ((RuntimeType.UNDEFINED) != (value_distributionType_type)) {
            const value_distributionType_value  = (value_distributionType as DistributionType)
            valueSerializer.writeInt32(value_distributionType_value.valueOf())
        }
        const value_updater  = value.updater
        let value_updater_type : int32 = RuntimeType.UNDEFINED
        value_updater_type = runtimeType(value_updater)
        valueSerializer.writeInt8(value_updater_type)
        if ((RuntimeType.UNDEFINED) != (value_updater_type)) {
            const value_updater_value  = value_updater!
            ParticleColorUpdaterOptionsInner_serializer.write(valueSerializer, value_updater_value)
        }
    }
}

export class EmitterOptionsInner_serializer {
    public static write(buffer: Serializer, value: EmitterOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_particle  = value.particle
        EmitterParticleOptions_serializer.write(valueSerializer, value_particle)
        const value_emitRate  = value.emitRate
        let value_emitRate_type : int32 = RuntimeType.UNDEFINED
        value_emitRate_type = runtimeType(value_emitRate)
        valueSerializer.writeInt8(value_emitRate_type)
        if ((RuntimeType.UNDEFINED) != (value_emitRate_type)) {
            const value_emitRate_value  = value_emitRate!
            valueSerializer.writeNumber(value_emitRate_value)
        }
        const value_shape  = value.shape
        let value_shape_type : int32 = RuntimeType.UNDEFINED
        value_shape_type = runtimeType(value_shape)
        valueSerializer.writeInt8(value_shape_type)
        if ((RuntimeType.UNDEFINED) != (value_shape_type)) {
            const value_shape_value  = (value_shape as ParticleEmitterShape)
            valueSerializer.writeInt32(value_shape_value.getOrdinal())
        }
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8(value_position_type)
        if ((RuntimeType.UNDEFINED) != (value_position_type)) {
            const value_position_value  = value_position!
            const value_position_value_0  = value_position_value[0]
            valueSerializer.writeLength(value_position_value_0);
            const value_position_value_1  = value_position_value[1]
            valueSerializer.writeLength(value_position_value_1);
        }
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8(value_size_type)
        if ((RuntimeType.UNDEFINED) != (value_size_type)) {
            const value_size_value  = value_size!
            const value_size_value_0  = value_size_value[0]
            valueSerializer.writeLength(value_size_value_0);
            const value_size_value_1  = value_size_value[1]
            valueSerializer.writeLength(value_size_value_1);
        }
        const value_annulusRegion  = value.annulusRegion
        let value_annulusRegion_type : int32 = RuntimeType.UNDEFINED
        value_annulusRegion_type = runtimeType(value_annulusRegion)
        valueSerializer.writeInt8(value_annulusRegion_type)
        if ((RuntimeType.UNDEFINED) != (value_annulusRegion_type)) {
            const value_annulusRegion_value  = value_annulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, value_annulusRegion_value)
        }
    }
}

export class ParticleOptionsInner_serializer {
    public static write(buffer: Serializer, value: ParticleOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_emitter  = value.emitter
        EmitterOptionsInner_serializer.write(valueSerializer, value_emitter)
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8(value_color_type)
        if ((RuntimeType.UNDEFINED) != (value_color_type)) {
            const value_color_value  = value_color!
            ParticleColorPropertyOptionsInner_serializer.write(valueSerializer, value_color_value)
        }
        const value_opacity  = value.opacity
        let value_opacity_type : int32 = RuntimeType.UNDEFINED
        value_opacity_type = runtimeType(value_opacity)
        valueSerializer.writeInt8(value_opacity_type)
        if ((RuntimeType.UNDEFINED) != (value_opacity_type)) {
            const value_opacity_value  = value_opacity!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, value_opacity_value)
        }
        const value_scale  = value.scale
        let value_scale_type : int32 = RuntimeType.UNDEFINED
        value_scale_type = runtimeType(value_scale)
        valueSerializer.writeInt8(value_scale_type)
        if ((RuntimeType.UNDEFINED) != (value_scale_type)) {
            const value_scale_value  = value_scale!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, value_scale_value)
        }
        const value_velocity  = value.velocity
        let value_velocity_type : int32 = RuntimeType.UNDEFINED
        value_velocity_type = runtimeType(value_velocity)
        valueSerializer.writeInt8(value_velocity_type)
        if ((RuntimeType.UNDEFINED) != (value_velocity_type)) {
            const value_velocity_value  = value_velocity!
            VelocityOptions_serializer.write(valueSerializer, value_velocity_value)
        }
        const value_acceleration  = value.acceleration
        let value_acceleration_type : int32 = RuntimeType.UNDEFINED
        value_acceleration_type = runtimeType(value_acceleration)
        valueSerializer.writeInt8(value_acceleration_type)
        if ((RuntimeType.UNDEFINED) != (value_acceleration_type)) {
            const value_acceleration_value  = value_acceleration!
            AccelerationOptionsInner_serializer.write(valueSerializer, value_acceleration_value)
        }
        const value_spin  = value.spin
        let value_spin_type : int32 = RuntimeType.UNDEFINED
        value_spin_type = runtimeType(value_spin)
        valueSerializer.writeInt8(value_spin_type)
        if ((RuntimeType.UNDEFINED) != (value_spin_type)) {
            const value_spin_value  = value_spin!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, value_spin_value)
        }
    }
}

export class DisturbanceFieldOptionsInner_serializer {
    public static write(buffer: Serializer, value: DisturbanceFieldOptionsInner): void {
        let valueSerializer : Serializer = buffer
        const value_strength  = value.strength
        let value_strength_type : int32 = RuntimeType.UNDEFINED
        value_strength_type = runtimeType(value_strength)
        valueSerializer.writeInt8(value_strength_type)
        if ((RuntimeType.UNDEFINED) != (value_strength_type)) {
            const value_strength_value  = value_strength!
            valueSerializer.writeNumber(value_strength_value)
        }
        const value_shape  = value.shape
        let value_shape_type : int32 = RuntimeType.UNDEFINED
        value_shape_type = runtimeType(value_shape)
        valueSerializer.writeInt8(value_shape_type)
        if ((RuntimeType.UNDEFINED) != (value_shape_type)) {
            const value_shape_value  = (value_shape as DisturbanceFieldShape)
            valueSerializer.writeInt32(value_shape_value.valueOf())
        }
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8(value_size_type)
        if ((RuntimeType.UNDEFINED) != (value_size_type)) {
            const value_size_value  = value_size!
            SizeNumberInner_serializer.write(valueSerializer, value_size_value)
        }
        const value_position  = value.position
        let value_position_type : int32 = RuntimeType.UNDEFINED
        value_position_type = runtimeType(value_position)
        valueSerializer.writeInt8(value_position_type)
        if ((RuntimeType.UNDEFINED) != (value_position_type)) {
            const value_position_value  = value_position!
            PositionNumberInner_serializer.write(valueSerializer, value_position_value)
        }
        const value_feather  = value.feather
        let value_feather_type : int32 = RuntimeType.UNDEFINED
        value_feather_type = runtimeType(value_feather)
        valueSerializer.writeInt8(value_feather_type)
        if ((RuntimeType.UNDEFINED) != (value_feather_type)) {
            const value_feather_value  = value_feather!
            valueSerializer.writeNumber(value_feather_value)
        }
        const value_noiseScale  = value.noiseScale
        let value_noiseScale_type : int32 = RuntimeType.UNDEFINED
        value_noiseScale_type = runtimeType(value_noiseScale)
        valueSerializer.writeInt8(value_noiseScale_type)
        if ((RuntimeType.UNDEFINED) != (value_noiseScale_type)) {
            const value_noiseScale_value  = value_noiseScale!
            valueSerializer.writeNumber(value_noiseScale_value)
        }
        const value_noiseFrequency  = value.noiseFrequency
        let value_noiseFrequency_type : int32 = RuntimeType.UNDEFINED
        value_noiseFrequency_type = runtimeType(value_noiseFrequency)
        valueSerializer.writeInt8(value_noiseFrequency_type)
        if ((RuntimeType.UNDEFINED) != (value_noiseFrequency_type)) {
            const value_noiseFrequency_value  = value_noiseFrequency!
            valueSerializer.writeNumber(value_noiseFrequency_value)
        }
        const value_noiseAmplitude  = value.noiseAmplitude
        let value_noiseAmplitude_type : int32 = RuntimeType.UNDEFINED
        value_noiseAmplitude_type = runtimeType(value_noiseAmplitude)
        valueSerializer.writeInt8(value_noiseAmplitude_type)
        if ((RuntimeType.UNDEFINED) != (value_noiseAmplitude_type)) {
            const value_noiseAmplitude_value  = value_noiseAmplitude!
            valueSerializer.writeNumber(value_noiseAmplitude_value)
        }
    }
}
