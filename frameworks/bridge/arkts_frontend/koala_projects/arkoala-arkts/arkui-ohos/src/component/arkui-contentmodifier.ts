import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ContentModifier } from "./common"
import { ArkUIGeneratedNativeModule } from "#components"
import { RadioConfiguration } from "./radio"
import { ButtonConfiguration } from "./button"
import { CheckBoxConfiguration } from "./checkbox"
import { ToggleConfiguration } from "./toggle"
import { RatingConfiguration } from "./rating"
import { SliderConfiguration } from "./slider"

export class ContentModifierHelper {
    //Radio
    private static contentModifierRadio_serialize(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRadio(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierRadio_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRadio(node)
    }

    public static contentModifierRadio(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RadioConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RadioConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRadio_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierRadio(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierRadio_serialize(node_casted)
    }
    //Button
    private static contentModifierButton_serialize(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierButton(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierButton_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierButton(node)
    }

    public static contentModifierButton(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ButtonConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
        ContentModifierHelper.contentModifierButton_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierButton(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierButton_serialize(node_casted)
    }
    //Checkbox
    private static contentModifierCheckbox_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckbox(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierCheckbox_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierCheckbox(node)
    }

    public static contentModifierCheckbox(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<CheckBoxConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
        ContentModifierHelper.contentModifierCheckbox_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierCheckbox(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierCheckbox_serialize(node_casted)
    }
    //Toggle
    private static contentModifierToggle_serialize(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierToggle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierToggle_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierToggle(node)
    }

    public static contentModifierToggle(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ToggleConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
        ContentModifierHelper.contentModifierToggle_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierToggle(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierToggle_serialize(node_casted)
    }
    //Rating
    private static contentModifierRating_serialize(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRating(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierRating_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRating(node)
    }

    public static contentModifierRating(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RatingConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RatingConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRating_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierRating(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierRating_serialize(node_casted)
    }
    //Slider
    private static contentModifierSlider_serialize(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierSlider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }

    private static resetContentModifierSlider_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierSlider(node)
    }

    public static contentModifierSlider(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<SliderConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: SliderConfiguration) => KPointer))
        ContentModifierHelper.contentModifierSlider_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }

    public static resetContentModifierSlider(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierSlider_serialize(node_casted)
    }
}