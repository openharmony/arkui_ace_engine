/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2023. All rights reserved.
 */

/**
 * Defines the reource which can use Astc.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 4.1.0(11)
 */
declare type AstcResource = {
  /**
   * srcs property, URI array of images to be concatenated.
   * @systemapi
   * @since 4.1.0(11)
   */
  sources: Array<string>;
  /**
   * column property, The number of small images per row of the texture large map after concatenation.
   * @systemapi
   * @since 4.1.0(11)
   */
  column: number;
}

/**
 * @interface CachedImageInterface
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 4.1.0(11)
 */
interface CachedImageInterface {
  /**
   * Set src to obtain images
   *
   * @param { PixelMap | ResourceStr | DrawableDescriptor | AstcResource } src
   * @returns { CachedImageAttribute }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 4.1.0(11)
   */
  (src: PixelMap | ResourceStr | DrawableDescriptor | AstcResource): CachedImageAttribute;
}

/**
 * Defines the CachedImage attribute from inheritance ImageAttribute
 *
 * @extends ImageAttribute
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 4.1.0(11)
 */
declare class CachedImageAttribute extends ImageAttribute {}

/**
 * Defines CachedImage Component.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 4.1.0(11)
 */
declare const CachedImage: CachedImageInterface;

/**
 * Defines CachedImage Component instance.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 4.1.0(11)
 */
declare const CachedImageInstance: CachedImageAttribute;
